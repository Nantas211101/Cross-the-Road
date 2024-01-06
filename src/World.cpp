#include "LaneFactoryTheme1.hpp"
#include "Obstacle.hpp"
#include <World.hpp>
#include <memory>

World::World(State::Context context)
: mWindow(*context.window)
, mWorldView(context.window->getDefaultView())
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y + 12000)
, mTextures(*context.textures)
, mFonts(*context.fonts)
, scrollDistance(0)
, mSceneGraph()
, mSceneLayers()
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, lanes()
, mainChar(nullptr)
, boundHealthBar(nullptr)
, healthBar(nullptr)
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
	if(ta.y <= viewSize.y / 2){

		// keep the mplayer position while reset the scroll (to make it infinity)
		mWorldView.setCenter(mSpawnPosition);
		mainChar->resetState();
		scrollDistance = 0;
		playerLaneIndex = 1;
	}

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

	buildMap();
	playerLaneIndex = 1;
	std::unique_ptr<MainChar> character(new MainChar(id, mTextures, playerLaneIndex, lanes));
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

	std::unique_ptr<SpriteNode> boundingHP(new SpriteNode(mTextures.get(Textures::BoundHealthBar)));
	boundingHP->setPosition(healthBarPos);
	boundHealthBar = boundingHP.get();
	mSceneLayers[AboveTitle]->attachChild(std::move(boundingHP));

	std::unique_ptr<SpriteNode> hpBar(new SpriteNode(mTextures.get(Textures::HealthBar)));
	hpBar->setTextureRect(healthBarPos, 309, 41);
	hpBar->setPosition(78, 16.5);
	healthBar = hpBar.get();
	boundHealthBar->attachChild(std::move(hpBar));

	std::unique_ptr<TextNode> healthDisplay(new TextNode(mFonts, ""));
	healthDisplay->setPosition(340, -13);
	mHealthDisplay = healthDisplay.get();
    boundHealthBar->attachChild(std::move(healthDisplay));
    updateHealthBar();
}

void World::updateHealthBar() {
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	sf::Vector2f healthBarPos(0, viewBounds.top);
	boundHealthBar->setPosition(healthBarPos);

	float curHP = mainChar->getHitpoints();
	float maxHP = mainChar->getMaxHP();
	healthBar->setTextureRect(healthBar->getPosition(), curHP * 309 / maxHP, 41);
	
	mHealthDisplay->setString(std::to_string((int)curHP) + " HP");
}

#include <iostream>
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
			std::cerr << theme << '\n';
			break;
		case 3:
			laneFactory = std::move(std::unique_ptr<LaneFactory>(new LaneFactoryTheme3(&mTextures, sf::Vector2f(-500, mWorldBounds.top + mWorldBounds.height - 400), level)));
			break;
	}
	// for(int i = 0; i < 12; i++) {
	// 	std::vector<std::unique_ptr<Lane>> randLanes;
	// 	if(i == 0){
	// 		randLanes = laneFactory->templateStartLane();
	// 	}
	// 	else{
	// 		randLanes = laneFactory->randomTemplateLane();
	// 	} 
	// 	for(auto& x : randLanes) {
	// 		lanes.push_back(x.get());
	// 		mSceneLayers[Title]->attachChild(std::move(x));
	// 	}
	// }
	std::vector<std::unique_ptr<Lane>> randLanes;
	randLanes = laneFactory->templateLane();
	for(auto& x : randLanes) {
		lanes.push_back(x.get());
		mSceneLayers[Title]->attachChild(std::move(x));
	}
	return;
}