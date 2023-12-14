#include <World.hpp>

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mFonts()
, lanes()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y + 2000)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, needAlign(false)
, isOnLog(false)
{

	mFonts.load(Fonts::Main, "Media/Sansation.ttf");
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures(){
	// Road
    mTextures.load(Textures::Road, "Media/Textures/Road/Road.png");
	mTextures.load(Textures::LavaRoad, "Media/Textures/Road/LavaRoad.png");
	mTextures.load(Textures::Road1, "Media/Textures/Road/Road1.png");
	mTextures.load(Textures::Soil, "Media/Textures/Road/Soil.png");

    mTextures.load(Textures::Elephant, "Media/Textures/Animal/Elephant.png");
    mTextures.load(Textures::Rhinoceros, "Media/Textures/Animal/Rhinoceros.png");
	mTextures.load(Textures::Cow, "Media/Textures/Animal/Cow.png");
    mTextures.load(Textures::Small_Dragon, "Media/Textures/Animal/Small_Dragon.png");
    mTextures.load(Textures::Red_Dragon, "Media/Textures/Animal/Red_Dragon.png");
    mTextures.load(Textures::Green_Dragon, "Media/Textures/Animal/Green_Dragon.png");
    mTextures.load(Textures::Blue_Twin_Head_Dragon, "Media/Textures/Animal/Blue_Twin_Head_Dragon.png");
    mTextures.load(Textures::Monster1, "Media/Textures/Animal/Monster1.png");

    mTextures.load(Textures::Traffic, "Media/Textures/Road/Traffic.png");
    mTextures.load(Textures::Truck, "Media/Textures/Vehicle/Truck.png");
    mTextures.load(Textures::Ambulance, "Media/Textures/Vehicle/Ambulance.png");
    mTextures.load(Textures::PoliceCar, "Media/Textures/Vehicle/PoliceCar.png");
    mTextures.load(Textures::SmallCar, "Media/Textures/Vehicle/SmallCar.png");
    mTextures.load(Textures::BlueCar, "Media/Textures/Vehicle/BlueCar.png");
    mTextures.load(Textures::YellowCar, "Media/Textures/Vehicle/YellowCar.png");
    mTextures.load(Textures::OldCar, "Media/Textures/Vehicle/OldCar.png");
    mTextures.load(Textures::SuperCar, "Media/Textures/Vehicle/SuperCar.png");

	// River
	mTextures.load(Textures::Log, "Media/Textures/River/Log.png");
	mTextures.load(Textures::Log1, "Media/Textures/River/Log1.png");
    mTextures.load(Textures::River, "Media/Textures/River/River.png");
	mTextures.load(Textures::LavaRiver, "Media/Textures/River/LavaRiver.png");
    // mTextures.load(Textures::LavaRiver1, "Media/Textures/LavaRiver1.png");
	//mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png"); // crocodile

	// Ground
    mTextures.load(Textures::Grass, "Media/Textures/Ground/Grass.png");
	mTextures.load(Textures::LavaGround, "Media/Textures/Ground/LavaGround.png");
	mTextures.load(Textures::LightGrass, "Media/Textures/Ground/LightGrass.png");
	mTextures.load(Textures::Tree1, "Media/Textures/Obstacle/Tree1.png");
	mTextures.load(Textures::Tree2, "Media/Textures/Obstacle/Tree2.png");
	mTextures.load(Textures::Tree3, "Media/Textures/Obstacle/Tree3.png");
	mTextures.load(Textures::Rock1, "Media/Textures/Obstacle/Rock1.png");
	mTextures.load(Textures::Rock2, "Media/Textures/Obstacle/Rock2.png");
	mTextures.load(Textures::Ruin1, "Media/Textures/Obstacle/Ruin1.png");
	mTextures.load(Textures::Ruin2, "Media/Textures/Obstacle/Ruin2.png");
	mTextures.load(Textures::Vocalno, "Media/Textures/Obstacle/Volcano.png");
	mTextures.load(Textures::Fire, "Media/Textures/Obstacle/Fire.png");
	// Railway
	mTextures.load(Textures::Railway, "Media/Textures/Railway/Railway.png");
	mTextures.load(Textures::RailwayLight, "Media/Textures/Railway/RailwayLight.png");
    //mTextures.load(Textures::Traffic, "Media/Textures/Railway/Traffic.png");
    mTextures.load(Textures::Train1, "Media/Textures/Railway/Train1.png");
    mTextures.load(Textures::Train2, "Media/Textures/Railway/Train2.png");
    mTextures.load(Textures::Train3, "Media/Textures/Railway/Train3.png");
	mTextures.load(Textures::Train4, "Media/Textures/Railway/Train4.png");

	// FinishLane
	mTextures.load(Textures::FinishLevel1, "Media/Textures/FinishLane/FinishLevel1.png");
	mTextures.load(Textures::FinishLevel2, "Media/Textures/FinishLane/FinishLevel2.png");
	mTextures.load(Textures::FinishLevel3, "Media/Textures/FinishLane/FinishLevel3.png");
	mTextures.load(Textures::FinishTheme1, "Media/Textures/FinishLane/FinishTheme1.png");
	mTextures.load(Textures::FinishTheme2, "Media/Textures/FinishLane/FinishTheme2.png");

	// Player
	mTextures.load(Textures::Standing1, "Media/Textures/Player/Player1/Standing.png");
	mTextures.load(Textures::Up1, "Media/Textures/Player/Player1/Up.png");
	mTextures.load(Textures::Down1, "Media/Textures/Player/Player1/Down.png");
	mTextures.load(Textures::Left1, "Media/Textures/Player/Player1/Left.png");
	mTextures.load(Textures::Right1, "Media/Textures/Player/Player1/Right.png");
	
	mTextures.load(Textures::Penguin, "Media/Textures/Player/Penguin.png");
	mTextures.load(Textures::Mallard, "Media/Textures/Player/Mallard.png");
	mTextures.load(Textures::Sheep, "Media/Textures/Player/Sheep.png");
	mTextures.load(Textures::Chicken, "Media/Textures/Player/Chicken.png");

	//Decorator
	mTextures.load(Textures::DecoTree1, "Media/Textures/Decorator/DecoTree1.png");
	mTextures.load(Textures::DecoTree2, "Media/Textures/Decorator/DecoTree2.png");
	mTextures.load(Textures::DecoFlower1, "Media/Textures/Decorator/DecoFlower1.png");
}

void World::update(sf::Time dt)
{
	// Scroll the world
	mWorldView.move(0, -100.f * dt.asSeconds());
	// Manipulating infinity scroll background.
	sf::Vector2f ta =  mWorldView.getCenter();
	sf::Vector2f viewSize = mWorldView.getSize();
	if(ta.y <= viewSize.y / 2){

		// keep the mplayer position while reset the scroll (to make it infinity)
		sf::Vector2f playerPos = mainChar->getPosition();
		sf::Vector2f mid = viewSize / 2.f;
		sf::Vector2f diffPos = playerPos - mid;
		mainChar->setPosition(mSpawnPosition + diffPos);
		mWorldView.setCenter(mSpawnPosition);
		mainChar->resetState();
	}

	//mainChar->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	timeToNextInput += dt;
	while (!mCommandQueue.isEmpty()){
		if(mainChar->isStanding()) {
			mSceneGraph.onCommand(mCommandQueue.pop(), dt);
			timeToNextInput = sf::Time::Zero;
		}
		else {
			mCommandQueue.pop();
		}
	}
	if(mainChar->isStanding())
		mainChar->setInLane(lanes);
	adaptPlayerVelocity();

	// Collision detection and response (may destroy entities)
	handleCollisions();

	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt);
	adaptPlayerPosition();
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
	mainChar->checkSceneCollision(*lanes[mainChar->getCurLane()], collisionPairs);

	for(SceneNode::Pair pair : collisionPairs)
	{
		if (matchesCategories(pair, Category::Player, Category::Log))
		{
			auto& player = static_cast<MainChar&>(*pair.first);
			auto& log = static_cast<Log&>(*pair.second);
			
			needAlign = true;
			isOnLog = true;
			if(mainChar->isStanding())
				mainChar->setVelocity(log.getVelocity().x, 0);
			break;
			// Apply pickup effect to player, destroy projectile
			// pickup.apply(player);
			// pickup.destroy();
		}
		else if (matchesCategories(pair, Category::Player, Category::River))
		{
			auto& player = static_cast<MainChar&>(*pair.first);
			auto& enemy = static_cast<River&>(*pair.second);

			// Collision: Player damage = enemy's remaining HP
			timeFromLastInvulnerable = invulnerableTime.getElapsedTime();
			if(timeFromLastInvulnerable > sf::seconds(0.1)){
				player.damage(5);
				invulnerableTime.restart();
			}
			// enemy.destroy();
		}
		else if (matchesCategories(pair, Category::Player, Category::Obstacle))
		{
			auto& player = static_cast<MainChar&>(*pair.first);
			auto& block = static_cast<Obstacle&>(*pair.second);

			// Collision: Player damage = enemy's remaining HP
			if(mainChar->getVelocity().y != 0)
				mainChar->backTolastLane();
			else
				mainChar->setPosition(mainChar->getLastPos());
			mainChar->stopMoving();
		}
	// 	if(matchesCategories(pair, Category::Player, Category::Road) || matchesCategories(pair, Category::Player, Category::Ground)) {
	// 		isOnLog = false;
	// 	}
	}
	// if(needAlign && !isOnLog && mainChar->isStanding()) {
	// 	needAlign = false;
	// 	mainChar->alignChar();
	// }
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

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}
	mSceneLayers[Title]->setReverse();
	LaneFactoryTheme1 laneFactory(&mTextures, sf::Vector2f(-500, mWorldBounds.top + mWorldBounds.height - 400));
	
	for(int i = 0; i < 10; i++) {
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
	std::unique_ptr<MainChar> character(new MainChar(MainChar::Player1, mTextures, mFonts, 1, lanes));
	mainChar = character.get();
	mSceneLayers[AboveTitle]->attachChild(std::move(character));
}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 0.f;

	sf::Vector2f position = mainChar->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mainChar->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	// sf::Vector2f velocity = mainChar->getVelocity();

	// // If moving diagonally, reduce velocity (to have always same velocity)
	// if (velocity.x != 0.f && velocity.y != 0.f)
	// 	mainChar->setVelocity(velocity / std::sqrt(2.f));
	// sf::Vector2f velocityAfterAdapt = mainChar->getVelocity();

	// Add scrolling velocity
	//mainChar->accelerate(0.f, 100.f);
}