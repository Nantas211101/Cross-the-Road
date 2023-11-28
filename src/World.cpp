#include "../include/World.h"

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, lanes()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x + 2500, mWorldView.getSize().y + 2000)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
{
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

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	LaneFactory laneFactory(sf::Vector2f(-500, mWorldBounds.top + mWorldBounds.height + 500));
	for(int i = 0; i < 10; i++) {
		std::vector<std::unique_ptr<Lane>> randLanes = laneFactory.randomTemplateLane();
		for(auto& x : randLanes) {
			lanes.push_back(x.get());
			mSceneLayers[AboveTitle]->attachChild(x->detachChild());
			mSceneLayers[Title]->attachChild(std::move(x));
		}
	}
}