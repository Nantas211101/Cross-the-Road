#include "../include/World.h"

#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures() 
, Grasses()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y + 2000)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	// Scroll the world
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	for(int i = 0; i < Grasses.size() ; i++) {
		sf::Vector2f pos = Grasses[i]->getPosition();
		if(pos.x >= 0) {
			Grasses[i]->setPosition(-224.f * 2, pos.y);
		}
	}
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

	sf::Vector2f spawnPos;
	spawnPos.x = -224 * 2;
	spawnPos.y = mWorldBounds.top + mWorldBounds.height + 500;
	while(spawnPos.y > mWorldBounds.top) {
		spawnPos.y -= 100.f;
		//random number of lanes:
		int numOfLane = 2 + rand() % 3;
		for(int i = 0; i < numOfLane; i++) {
			std::unique_ptr<Lane> grass(new Grass(spawnPos, mTextures));
			Grasses.push_back(grass.get());
			grass->setPosition(spawnPos);
			// if(!river->isReverse())
			// 	river->setVelocity(100.f, 0.f);
			// else
			// 	river->setVelocity(-100.f, 0.f);
			spawnPos.y -= 50;
			mSceneLayers[AboveTitle]->attachChild(grass->detachChild());
			mSceneLayers[Title]->attachChild(std::move(grass));
		}
	}
}
