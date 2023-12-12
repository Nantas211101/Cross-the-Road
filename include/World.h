#pragma once

#include "SceneNode.h"
#include "World/LaneFactory.h"
#include "World/LaneFactoryTheme1.h"
#include "World/LaneFactoryTheme2.h"
#include "World/Decorator.h"
#include "CommandQueue.h"
#include "MainChar.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"

#include <random>
#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

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
		bool								needAlign;
		bool								isOnLog;
};