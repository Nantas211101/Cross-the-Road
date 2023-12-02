#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>

const std::string Path_TitleScreen = "Media/Textures/TitleScreen.jpg";
const std::string Path_chickenMain = "Media/Textures/chicken.png";
const std::string Path_penguinMain = "Media/Textures/Penguin.png";
const std::string Path_sheepMain = "Media/Textures/Sheep.png";
const std::string Path_mallardMain = "Media/Textures/Mallard.png";

const int numOfHeight = 3;

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures() 
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y * numOfHeight)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - (mWorldView.getSize().y / 2.f))
, mScrollSpeed(-200.f)
, mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	// Scroll the world, reset player velocity
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	// Manipulating infinity scroll background.
	sf::Vector2f ta =  mWorldView.getCenter();
	sf::Vector2f viewSize = mWorldView.getSize();
	if(ta.y <= viewSize.y / 2){

		// keep the mplayer position while reset the scroll (to make it infinity)
		sf::Vector2f playerPos = mPlayerAircraft->getPosition();
		sf::Vector2f mid = viewSize / 2.f;
		sf::Vector2f diffPos = playerPos - mid;
		mPlayerAircraft->setPosition(mSpawnPosition + diffPos);
		mWorldView.setCenter(mSpawnPosition);
	}

	mPlayerAircraft->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty()){
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}
	adaptPlayerVelocity();

	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt);
	adaptPlayerPosition();
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::initMainCharID(MainChar::Type id)
{
	mPlayerAircraft->setTexture(MainChar::toTextureID(id), mTextures);
}

void World::loadTextures()
{
    mTextures.load(Textures::TitleScreen, Path_TitleScreen);
	mTextures.load(Textures::chicken, Path_chickenMain);
    mTextures.load(Textures::penguin, Path_penguinMain);
    mTextures.load(Textures::sheep, Path_sheepMain);
    mTextures.load(Textures::mallard, Path_mallardMain);
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
	sf::Texture& texture = mTextures.get(Textures::TitleScreen);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	mBackGround = backgroundSprite.get();
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's aircraft
	std::unique_ptr<MainChar> leader(new MainChar(MainChar::Chicken, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setScale(0.3, 0.3);
	mSceneLayers[Air]->attachChild(std::move(leader));
}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
	sf::Vector2f velocityAfterAdapt = mPlayerAircraft->getVelocity();

	// Add scrolling velocity
	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}