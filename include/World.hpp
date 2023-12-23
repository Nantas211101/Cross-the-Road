#pragma once

#include <SceneNode.hpp>
#include <LaneFactory.hpp>
#include <LaneFactoryTheme1.hpp>
#include <LaneFactoryTheme2.hpp>
#include <Decorator.hpp>
#include <CommandQueue.hpp>
#include <MainChar.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <State.hpp>
#include <SpriteNode.hpp>

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
		explicit		 					World(State::Context context);
		void								update(sf::Time dt);
		void								draw();
		CommandQueue&						getCommandQueue();

	private:
		void								buildScene(MainChar::Type id);
		void 								adaptPlayerPosition();
		void								handleCollisions();
		void								scroll(sf::Time dt);
		void								buildHealthBar();
		void								updateHealthBar();

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
		sf::FloatRect						mWorldBounds;
		TextureHolder&						mTextures;
		FontHolder&							mFonts;
		const float							scrollSpeed = -200.f;
		const float							scrollSpeedToPlayer = -50.f;
		float								scrollDistance;
		int									playerLaneIndex;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::Vector2f						mSpawnPosition;
		std::vector<Lane*> 					lanes;
		MainChar*							mainChar;

		SpriteNode*							boundHealthBar;
		SpriteNode*							healthBar;
    	TextNode* 							mHealthDisplay;
};