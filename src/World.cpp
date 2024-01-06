#include "LaneFactoryTheme1.hpp"
#include "Obstacle.hpp"
#include <World.hpp>
#include <MainChar1.hpp>
#include <MainChar2.hpp>
#include <MainChar3.hpp>
#include <MainChar4.hpp>
#include <MainChar5.hpp>
#include <memory>

World::World(State::Context context)
: mContext(context)
, playingState(InGameState::Playing)
, money(0)
, mWindow(*context.window)
, mWorldView(context.window->getDefaultView())
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y + 12000)
, mTextures(*context.textures)
, mFonts(*context.fonts)
, mSound(*context.sounds)
, scrollDistance(0)
, mSceneGraph()
, mSceneLayers()
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, lanes()
, mainChar(nullptr)
, moneyBar(nullptr)
, moneyDisplay(nullptr)
, boundBar(nullptr)
, healthBar(nullptr)
, manaBar(nullptr)
, mHealthDisplay(nullptr)
, timeSinceLastDamage()
{
	buildScene(context.player->getMainCharID());
	buildMainChar();
	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
	buildHealthBar();
	buildMoneyInFo();
}

void World::update(sf::Time dt)
{
	if(playingState == InGameState::Win || playingState == InGameState::Lose)
		return;
	// Scroll the world
	scroll(dt);

	// Manipulating infinity scroll background.
	sf::Vector2f ta =  mWorldView.getCenter();
	sf::Vector2f viewSize = mWorldView.getSize();
	// if(ta.y <= viewSize.y / 2){

	// 	// keep the mplayer position while reset the scroll (to make it infinity)
	// 	mWorldView.setCenter(mSpawnPosition);
	// 	mainChar->resetState();
	// 	scrollDistance = 0;
	// 	playerLaneIndex = highestBound = 1;
	// }

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty()){
		if(mainChar->isStanding()) {
			mSceneGraph.onCommand(mCommandQueue.pop(), dt);
		}
		else {
			mCommandQueue.pop();
		}
	}
	while(!soundCommandQueue.isEmpty()) {
		mSceneGraph.onCommand(soundCommandQueue.pop(), dt);
	}

	// Collision detection and response (may destroy entities)
	handleCollisions();

	// Regular update step, adapt position
	mSceneGraph.update(dt);
	if(mainChar->isDead()) {
		playingState = InGameState::Lose;
	}
	adaptPlayerPosition();
	updateHealthBar();
	updateMana(dt);
	updateSound();
	updateMoneyBar();
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	int curLane = mainChar->getCurLane();
	mainChar->checkSceneCollision(*lanes[curLane], collisionPairs);
	if(curLane + 1 < lanes.size())
		mainChar->checkSceneCollision(*lanes[curLane + 1], collisionPairs);
	if(curLane - 1 >= 0) 
		mainChar->checkSceneCollision(*lanes[curLane - 1], collisionPairs);

	bool onRiver = false;
    sf::Time timeFromLastDamage = timeSinceLastDamage.getElapsedTime();
	for(SceneNode::Pair pair : collisionPairs) {
		if (matchesCategories(pair, Category::Player, Category::Log)) {
			auto& log = static_cast<Log&>(*pair.second);
			onRiver = false;
			if(mainChar->isStanding())
				mainChar->setVelocity(log.getVelocity().x, 0);
			break;
		}
		else if (matchesCategories(pair, Category::Player, Category::River)) {
			onRiver = true;
			
		}
		else if(matchesCategories(pair, Category::Player, Category::Lane)) {
			onRiver = false;
			break;
		}
	}
	for(SceneNode::Pair pair : collisionPairs) {
		if (matchesCategories(pair, Category::Player, Category::Obstacle)) {
			if(timeFromLastDamage >= damageGap) {
				auto& obstacle = static_cast<Obstacle&>(*pair.second);
				mainChar->damage(obstacle.getDamage());
				obstacle.playLocalSound(soundCommandQueue);
				timeSinceLastDamage.restart();
			}
			mainChar->backTolastPos();
			mainChar->stopMoving();
		}
		else if(matchesCategories(pair, Category::Player, Category::Vehicle)) {
			if(timeFromLastDamage >= damageGap) {
				auto& vehicle = static_cast<Vehicle&>(*pair.second);
				mainChar->damage(vehicle.getDamage());
				vehicle.playLocalSound(soundCommandQueue);
				timeSinceLastDamage.restart();
			}
		}
		else if(matchesCategories(pair, Category::Player, Category::Animal)) {
			if(timeFromLastDamage >= damageGap) {
				auto& animal = static_cast<Animal&>(*pair.second);
				mainChar->damage(animal.getDamage());
				animal.playLocalSound(soundCommandQueue);
				timeSinceLastDamage.restart();
			}
		}
		else if(matchesCategories(pair, Category::Player, Category::Train)) {
			if(timeFromLastDamage >= damageGap) {
				auto& train = static_cast<Train&>(*pair.second);
				mainChar->damage(train.getDamage());
				train.playLocalSound(soundCommandQueue);
				timeSinceLastDamage.restart();
			}
		}
		else if(matchesCategories(pair, Category::Player, Category::Coin)) {
			++money;
			auto& coin = static_cast<Obstacle&>(*pair.second);
			coin.playLocalSound(soundCommandQueue);
			coin.markedForRemoval();
			mSceneLayers[Title]->removeWrecks();
		}
		else if(matchesCategories(pair, Category::Player, Category::WinLane)) {
			playingState = InGameState::Win;
		}
	}
	sf::Time timeFromLastRiverDamage = timeSinceLastDamageByRiver.getElapsedTime();
	if(onRiver) {
		if(timeFromLastRiverDamage >= damageGapByRiver) {
			mainChar->damage(5);
			timeSinceLastDamageByRiver.restart();
		}
	}
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue &World::getCommandQueue()
{
    return mCommandQueue;
}

World::InGameState World::getInGameState() {
    return playingState;
}

int World::getMoney() {
    return money;
}

void World::buildScene(MainChar::Type id)
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}
	mSceneLayers[Title]->setReverse();

	buildMap();
	// Add sound effect node
	std::unique_ptr<SoundNode> soundNode(new SoundNode(mSound));
	mSceneGraph.attachChild(std::move(soundNode));
}

void World::adaptPlayerPosition() {
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

	sf::Vector2f position = mainChar->getPosition();
	if(position.x <= viewBounds.left) {
		mainChar->setPosition(1, position.y);
		mainChar->stopMoving();
	}
	else if(position.x >= viewBounds.left + viewBounds.width - 50) {
		mainChar->setPosition(viewBounds.left + viewBounds.width - 51, position.y);
		mainChar->stopMoving();
	}
	else if(position.y >= viewBounds.top + viewBounds.height) {
		playingState = InGameState::Lose;
	}
	else if(position.y <= viewBounds.top) {
		mainChar->backTolastPos();
		mainChar->stopMoving();
	}
}

void World::scroll(sf::Time dt) {
	int curLane = mainChar->getCurLane();
	if(curLane > playerLaneIndex) {
		scrollDistance += Lane::distanceBetweenLane;
		++playerLaneIndex;
	}
	else if(curLane < playerLaneIndex) {
		scrollDistance -= Lane::distanceBetweenLane;
		--playerLaneIndex;
	}
	float laneStep = scrollSpeed * dt.asSeconds();
	if(scrollDistance > 0) {
		scrollDistance += laneStep;
		mWorldView.move(0, laneStep);
	}
	else {
		float step = scrollSpeedToPlayer * dt.asSeconds();
		scrollDistance += step;
		mWorldView.move(0, step);
	}
}

void World::buildHealthBar() {
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	sf::Vector2f healthBarPos(0, viewBounds.top);

	std::unique_ptr<SpriteNode> boundingHP(new SpriteNode(mTextures.get(Textures::BoundBar)));
	boundingHP->setPosition(healthBarPos);
	boundBar = boundingHP.get();
	mSceneLayers[AboveTitle]->attachChild(std::move(boundingHP));

	std::unique_ptr<SpriteNode> hpBar(new SpriteNode(mTextures.get(Textures::HealthBar)));
	hpBar->setTextureRect(healthBarPos, 306, 30.64);
	hpBar->setPosition(78, 12);
	healthBar = hpBar.get();
	boundBar->attachChild(std::move(hpBar));

	std::unique_ptr<SpriteNode> mpBar(new SpriteNode(mTextures.get(Textures::ManaBar)));
	mpBar->setTextureRect(healthBarPos, 306, 19);
	mpBar->setPosition(78, 42);
	manaBar = mpBar.get();
	boundBar->attachChild(std::move(mpBar));

	std::unique_ptr<TextNode> healthDisplay(new TextNode(mFonts, ""));
	healthDisplay->setPosition(334, -25);
	mHealthDisplay = healthDisplay.get();
    boundBar->attachChild(std::move(healthDisplay));
    updateHealthBar();
}

void World::updateHealthBar() {
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	sf::Vector2f healthBarPos(0, viewBounds.top);
	boundBar->setPosition(healthBarPos);

	float curHP = mainChar->getHitpoints();
	float maxHP = mainChar->getMaxHP();
	healthBar->setTextureRect(healthBar->getPosition(), curHP * 306 / maxHP, 30.64);

	float curMP = mainChar->getManaPoints();
	float maxMP = mainChar->getMaxMP();
	manaBar->setTextureRect(manaBar->getPosition(), curMP * 306 / maxMP, 19);
	
	mHealthDisplay->setString(std::to_string((int)curHP) + " HP");
}

void World::buildMap(){
	int theme = *mContext.theme;
	int level = *mContext.currentLevel;
	std::unique_ptr<LaneFactory> laneFactory;
	switch(theme){
		case 1:
			laneFactory = std::move(std::unique_ptr<LaneFactory>(new LaneFactoryTheme1(&mTextures, sf::Vector2f(-500, mWorldBounds.top + mWorldBounds.height - 400), level)));
			break;
		case 2:
			laneFactory = std::move(std::unique_ptr<LaneFactory>(new LaneFactoryTheme2(&mTextures, sf::Vector2f(-500, mWorldBounds.top + mWorldBounds.height - 400), level)));
			break;
		case 3:
			laneFactory = std::move(std::unique_ptr<LaneFactory>(new LaneFactoryTheme3(&mTextures, sf::Vector2f(-500, mWorldBounds.top + mWorldBounds.height - 400), level)));
			break;
	}
	std::vector<std::unique_ptr<Lane>> randLanes;
	randLanes = laneFactory->templateLane();
	for(auto& x : randLanes) {
		lanes.push_back(x.get());
		mSceneLayers[Title]->attachChild(std::move(x));
	}
	return;
}

void World::updateMana(sf::Time dt) {
	int curLane = mainChar->getCurLane();
	timeSinceLastAddMana += dt;
	if(curLane > highestBound) {
		mainChar->addMana(20);
		highestBound = curLane;
		timeSinceLastAddMana = sf::Time::Zero;
	}
	else if(timeSinceLastAddMana > timeEachAddMana) {
		mainChar->addMana(1);
		timeSinceLastAddMana = sf::Time::Zero;
	}
}

void World::buildMainChar() {
	playerLaneIndex = highestBound = 1;
	std::unique_ptr<MainChar> character;
	auto id = mContext.player->getMainCharID();
	if(id == MainChar::Type::Player1) {
		character = std::move(std::unique_ptr<MainChar>(new MainChar1(mTextures, soundCommandQueue, playerLaneIndex, lanes)));
	}
	else if(id == MainChar::Type::Player2) {
		character = std::move(std::unique_ptr<MainChar>(new MainChar2(mTextures, soundCommandQueue, playerLaneIndex, lanes)));
	}
	else if(id == MainChar::Type::Player3) {
		character = std::move(std::unique_ptr<MainChar>(new MainChar3(mTextures, soundCommandQueue, playerLaneIndex, lanes)));
	}
	else if(id == MainChar::Type::Player4) {
		character = std::move(std::unique_ptr<MainChar>(new MainChar4(mTextures, soundCommandQueue, playerLaneIndex, lanes)));
	}
	else if(id == MainChar::Type::Player5) {
		character = std::move(std::unique_ptr<MainChar>(new MainChar5(mTextures, soundCommandQueue, playerLaneIndex, lanes)));
	}
	mainChar = character.get();
	mSceneLayers[AboveTitle]->attachChild(std::move(character));
}

void World::updateSound() {
	mSound.setListenerPosition(mainChar->getPosition());
	mSound.removeStoppedSounds();
}

void World::buildMoneyInFo() {
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	sf::Vector2f moneyBarPos(1419, viewBounds.top + 16);

	std::unique_ptr<SpriteNode> moneybar(new SpriteNode(mTextures.get(Textures::MoneyBar)));
	moneybar->setPosition(moneyBarPos);
	moneyBar = moneybar.get();
	mSceneLayers[AboveTitle]->attachChild(std::move(moneybar));

	std::unique_ptr<TextNode> moneyInfo(new TextNode(mFonts, ""));
	moneyInfo->setCharacterSize(35);
	moneyInfo->setPosition(60, -18);
	moneyInfo->setFillColor(sf::Color::Black);
	moneyDisplay = moneyInfo.get();
    moneyBar->attachChild(std::move(moneyInfo));
	updateMoneyBar();
}

void World::updateMoneyBar() {
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	sf::Vector2f moneyBarPos(1419, viewBounds.top + 16);

	moneyBar->setPosition(moneyBarPos);
	moneyDisplay->setString(std::to_string(money));
}