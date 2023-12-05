#pragma once

#include "SceneNode.h"
#include "World/LaneFactory.h"
#include "CommandQueue.h"
#include "MainChar.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>
#include <random>
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
		CommandQueue&						getCommandQueue();

	private:
		void								loadTextures();
		void								buildScene();
		void 								adaptPlayerPosition();
		void 								adaptPlayerVelocity();
		void								handleCollisions();
		
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
		FontHolder							mFonts;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;
		sf::Time							timeToNextInput;
		sf::Clock							invulnerableTime;
		sf::Time							timeFromLastInvulnerable;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;
		std::vector<Lane*> 					lanes;
		MainChar*							mainChar;
};