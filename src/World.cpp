#include "../include/World.h"

#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures() 
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(0)
, mEnemySpawnPoints()
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
	mTextures.load(Textures::Log, "../../Media/Textures/Log.png");
	mTextures.load(Textures::River, "../../Media/Textures/River.png");
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

	sf::Texture& texture1 =  mTextures.get(Textures::River);
	texture1.setRepeated(true);

	sf::IntRect textureRect1(0, 0, 2000, 100);
	std::unique_ptr<Lane> river(new River(mTextures, textureRect1));
	river->setPosition(sf::Vector2f(-100.f, 40.f));
	mSceneLayers[Title]->attachChild(std::move(river));

	// sf::Texture& texture1 = mTextures.get(Textures::River);
	// sf::IntRect textureRect1(0, 0, 1000, 100);
	// texture1.setRepeated(true);

	// std::unique_ptr<SpriteNode> background(new SpriteNode(texture1, textureRect1));
	// background->setPosition(mWorldBounds.left, mWorldBounds.top + 100);
	// mSceneLayers[Title]->attachChild(std::move(background));
}
