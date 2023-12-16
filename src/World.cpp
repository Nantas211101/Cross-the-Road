#include <World.hpp>

World::World(State::Context context)
: mWindow(*context.window)
, mWorldView(context.window->getDefaultView())
, mTextures(*context.textures)
, mFonts(*context.fonts)
, lanes()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y + 2000)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, needAlign(false)
, isOnLog(false)
{
	buildScene(context.player->getMainCharID());

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
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
	std::unique_ptr<MainChar> character(new MainChar(id, mTextures, mFonts, 1, lanes));
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
