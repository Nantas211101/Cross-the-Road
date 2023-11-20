#pragma once

#include "TextureHolder.h"
#include "SceneNode.h"
#include "Log.h"
#include "Lane.h"
#include "River.h"
#include "Road.h"
#include "Animal.h"
#include "Grass.h"
#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>
#include <cmath>

// Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
	public:
		explicit							World(sf::RenderWindow& window);
		void								update(sf::Time dt);
		void								draw();


	private:
		void								loadTextures();
		void								buildScene();
		
	private:
		enum Layer
		{
			Background,
			Title,
			AboveTitle,
			LayerCount
		};
	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;
		std::vector<Lane*> 					lanes;
};