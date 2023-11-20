#include "../include/World.h"

#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures() 
, lanes()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x + 2000, mWorldView.getSize().y + 2000)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	// Scroll the world
	mWorldView.move(0, -100.f * dt.asSeconds());
	// Apply movements
	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextures.load(Textures::Desert, "../../Media/Textures/Desert.png");
	mTextures.load(Textures::River, "../../Media/Textures/River.png");
	mTextures.load(Textures::Road, "../../Media/Textures/Road.png");
	mTextures.load(Textures::Grass, "../../Media/Textures/Grass.png");
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

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	sf::Texture& texture1 =  mTextures.get(Textures::Grass);
	texture1.setRepeated(true);

	// sf::Vector2f spawnPos;
	// spawnPos.x = -500; // < 0
	// spawnPos.y = mWorldBounds.top + mWorldBounds.height + 500;
	// while(spawnPos.y > mWorldBounds.top) {
	// 	spawnPos.y -= 100.f;
	// 	//random number of lanes:
	// 	int numOfLane = 1 + rand() % 3;
	// 	for(int i = 0; i < numOfLane; i++) {
	// 		std::unique_ptr<Lane> river(new River(spawnPos, mTextures));
	// 		rivers.push_back(river.get());
	// 		river->setPosition(spawnPos);
	// 		spawnPos.y -= 150;
	// 		mSceneLayers[AboveTitle]->attachChild(river->detachChild());
	// 		mSceneLayers[Title]->attachChild(std::move(river));
	// 	}
	// }

	sf::Texture& textureRoad =  mTextures.get(Textures::Road);
	textureRoad.setRepeated(true);

	sf::Vector2f spawnPos;
	spawnPos.x = -500; // < 0
	spawnPos.y = mWorldBounds.top + mWorldBounds.height + 500;
	while(spawnPos.y > mWorldBounds.top) {
		//random number of lanes:
		int numOfLane = 1 + rand() % 3;
		int randLaneKind = 1 + rand() % 3;
		for(int i = 0; i < numOfLane; i++) {
			std::unique_ptr<Lane> lane;
			switch(randLaneKind) {
			case 1:
				lane = std::move(std::unique_ptr<Lane>(new Road(spawnPos, mTextures)));
				break;
			case 2:
				lane = std::move(std::unique_ptr<Lane>(new River(spawnPos, mTextures)));
				break;
			case 3:
				lane = std::move(std::unique_ptr<Lane>(new Grass(spawnPos, mTextures)));
				break;
			}
			lanes.push_back(lane.get());
			lane->setPosition(spawnPos);
			spawnPos.y -= 150;
			mSceneLayers[AboveTitle]->attachChild(lane->detachChild());
			mSceneLayers[Title]->attachChild(std::move(lane));
		}
	}
}
