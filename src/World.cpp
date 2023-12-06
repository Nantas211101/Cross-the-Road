#include "../include/World.h"

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
{
	mFonts.load(Fonts::Main, "../../Media/Sansation.ttf");
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures(){
	// Road
    mTextures.load(Textures::Road, "../../Media/Textures/Road.png");
	mTextures.load(Textures::Road1, "../../Media/Textures/Road1.png");

    mTextures.load(Textures::Elephant, "../../Media/Textures/Elephant.png");
    mTextures.load(Textures::Rhinoceros, "../../Media/Textures/Rhinoceros.png");
    mTextures.load(Textures::Small_Dragon, "../../Media/Textures/Small_Dragon.png");
    mTextures.load(Textures::Red_Dragon, "../../Media/Textures/Red_Dragon.png");
    mTextures.load(Textures::Green_Dragon, "../../Media/Textures/Green_Dragon.png");
    mTextures.load(Textures::Blue_Twin_Head_Dragon, "../../Media/Textures/Blue_Twin_Head_Dragon.png");
    
    mTextures.load(Textures::Traffic, "../../Media/Textures/Traffic.png");
    mTextures.load(Textures::Truck, "../../Media/Textures/Truck.png");
    mTextures.load(Textures::Ambulance, "../../Media/Textures/Ambulance.png");
    mTextures.load(Textures::PoliceCar, "../../Media/Textures/PoliceCar.png");
    mTextures.load(Textures::SmallCar, "../../Media/Textures/SmallCar.png");
    mTextures.load(Textures::BlueCar, "../../Media/Textures/BlueCar.png");
    mTextures.load(Textures::YellowCar, "../../Media/Textures/YellowCar.png");
    mTextures.load(Textures::OldCar, "../../Media/Textures/OldCar.png");
    mTextures.load(Textures::SuperCar, "../../Media/Textures/SuperCar.png");

	// River
	mTextures.load(Textures::Log, "../../Media/Textures/Log.png");
    mTextures.load(Textures::River, "../../Media/Textures/River.png");
    //mTextures.load(Textures::Eagle, "../../Media/Textures/Eagle.png"); // crocodile

	// Grass
	mTextures.load(Textures::Tree, "../../Media/Textures/Tree.png");
    mTextures.load(Textures::Grass, "../../Media/Textures/Grass.png");

	// Railway
	mTextures.load(Textures::Railway, "../../Media/Textures/Railway.png");
    //mTextures.load(Textures::Traffic, "../../Media/Textures/Traffic.png");
    mTextures.load(Textures::Train1, "../../Media/Textures/Train1.png");
    mTextures.load(Textures::Train2, "../../Media/Textures/Train2.png");
    mTextures.load(Textures::Train3, "../../Media/Textures/Train3.png");

	// Player
	mTextures.load(Textures::Penguin, "../../Media/Textures/Player/Penguin.png");
	mTextures.load(Textures::Mallard, "../../Media/Textures/Player/Mallard.png");
	mTextures.load(Textures::Sheep, "../../Media/Textures/Player/Sheep.png");
	mTextures.load(Textures::Chicken, "../../Media/Textures/Player/Chicken.png");
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
	}

	mainChar->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	timeToNextInput += dt;
	while (!mCommandQueue.isEmpty()){
		if(timeToNextInput > sf::seconds(0.3)) {
			mSceneGraph.onCommand(mCommandQueue.pop(), dt);
			timeToNextInput = sf::Time::Zero;
		}
		else {
			mCommandQueue.pop();
		}
	}
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
	mainChar->checkSceneCollision(*mSceneLayers[AboveTitle], collisionPairs);
	mainChar->checkSceneCollision(*mSceneLayers[Title], collisionPairs);

	for(SceneNode::Pair pair : collisionPairs)
	{
		

		if (matchesCategories(pair, Category::Player, Category::Log))
		{
			auto& player = static_cast<MainChar&>(*pair.first);
			auto& log = static_cast<Log&>(*pair.second);
			
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
			if(timeFromLastInvulnerable > sf::seconds(1)){
				player.damage(5);
				invulnerableTime.restart();
			}
			// enemy.destroy();
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

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	LaneFactory laneFactory(&mTextures, sf::Vector2f(-500, mWorldBounds.top + mWorldBounds.height + 500));
	for(int i = 0; i < 10; i++) {
		std::vector<std::unique_ptr<Lane>> randLanes = laneFactory.randomTemplateLane();
		for(auto& x : randLanes) {
			lanes.push_back(x.get());
			mSceneLayers[AboveTitle]->attachChild(x->detachChild());
			mSceneLayers[Title]->attachChild(std::move(x));
		}
	}
	std::unique_ptr<MainChar> character(new MainChar(MainChar::Penguin, mTextures, mFonts));
	mainChar = character.get();
	character->setPosition(575, mSpawnPosition.y + 75);
	mSceneLayers[AboveTitle]->attachChild(std::move(character));
}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 20.f;

	sf::Vector2f position = mainChar->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mainChar->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mainChar->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mainChar->setVelocity(velocity / std::sqrt(2.f));
	sf::Vector2f velocityAfterAdapt = mainChar->getVelocity();

	// Add scrolling velocity
	//mainChar->accelerate(0.f, 100.f);
}