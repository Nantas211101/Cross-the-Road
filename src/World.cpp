#include "Obstacle.hpp"
#include <World.hpp>
#include <Player1.hpp>
#include <Player2.hpp>
#include <Player3.hpp>

World::World(State::Context context)
: mWindow(*context.window)
, mWorldView(context.window->getDefaultView())
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y + 1000)
, mTextures(*context.textures)
, mFonts(*context.fonts)
, scrollDistance(0)
, mSceneGraph()
, mSceneLayers()
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, lanes()
, mainChar(nullptr)
, boundBar(nullptr)
, healthBar(nullptr)
, manaBar(nullptr)
, mHealthDisplay(nullptr)
, mContext(context)
{
	buildScene(context.player->getMainCharID());
	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
	buildHealthBar();
}


void World::update(sf::Time dt)
{
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

	// Collision detection and response (may destroy entities)
	handleCollisions();

	// Regular update step, adapt position
	mSceneGraph.update(dt);
	if(mainChar->getHitpoints() <= 0) {
		// Gameover
	}
	adaptPlayerPosition();
	updateHealthBar();
	updateMana(dt);
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

		if (matchesCategories(pair, Category::Player, Category::Obstacle)) {
			auto& obstacle = static_cast<Obstacle&>(*pair.second);
			mainChar->damage(obstacle.getDamage());
			mainChar->backTolastPos();
			mainChar->stopMoving();
		}
		else if(matchesCategories(pair, Category::Player, Category::Vehicle)) {
			auto& vehicle = static_cast<Vehicle&>(*pair.second);
			mainChar->damage(vehicle.getDamage());
		}
		else if(matchesCategories(pair, Category::Player, Category::Animal)) {
			auto& animal = static_cast<Animal&>(*pair.second);
			mainChar->damage(animal.getDamage());
		}
		else if(matchesCategories(pair, Category::Player, Category::Train)) {
			auto& train = static_cast<Train&>(*pair.second);
			//mainChar->damage(train.getDamage());
		}
	}
	if(onRiver) {
	// Game over
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

	LaneFactoryTheme2 laneFactory(&mTextures, sf::Vector2f(-500, mWorldBounds.top + mWorldBounds.height - 400));
	
	for(int i = 0; i < 60; i++) {
		std::vector<std::unique_ptr<Lane>> randLanes;
		if(i == 0){
			randLanes = laneFactory.templateStartLane();
		}
		else{
			randLanes = laneFactory.randomTemplateLane();
		} 
		for(auto& x : randLanes) {
			lanes.push_back(x.get());
			mSceneLayers[Title]->attachChild(std::move(x));
		}
	}
	playerLaneIndex = highestBound = 1;
	std::unique_ptr<MainChar> character(new Player2(mTextures, playerLaneIndex, lanes));
	mainChar = character.get();
	mSceneLayers[AboveTitle]->attachChild(std::move(character));
}

void World::adaptPlayerPosition() {
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

	sf::Vector2f position = mainChar->getPosition();
	if(position.x <= viewBounds.left) {
		mainChar->setPosition(1, position.y);
		mainChar->stopMoving();
	}
	else if(position.x >= viewBounds.left + viewBounds.width) {
		mainChar->setPosition(viewBounds.left + viewBounds.width - 1, position.y);
		mainChar->stopMoving();
	}
	else if(position.y >= viewBounds.left + viewBounds.width) {
		// Gameover
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
	manaBar->setTextureRect(manaBar->getPosition(),  curMP * 306 / maxMP, 19);
	
	mHealthDisplay->setString(std::to_string((int)curHP) + " HP");
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
		mainChar->addMana(5);
		timeSinceLastAddMana = sf::Time::Zero;
	}
}