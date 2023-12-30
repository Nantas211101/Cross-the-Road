#pragma once

#include <SceneNode.hpp>
#include <LaneFactory.hpp>
#include <LaneFactoryTheme1.hpp>
#include <LaneFactoryTheme2.hpp>
#include <LaneFactoryTheme3.hpp>
#include <Decorator.hpp>
#include <CommandQueue.hpp>
#include <MainChar.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <State.hpp>
#include <SpriteNode.hpp>
#include <SoundNode.hpp>
#include <SoundPlayer.hpp>

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
		void								updateSound();

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
		SoundPlayer&						mSound;

		const float							scrollSpeed = -200.f;
		const float							scrollSpeedToPlayer = -50.f;
		float								scrollDistance;
		int									playerLaneIndex;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;
		CommandQueue						soundCommandQueue;

		sf::Vector2f						mSpawnPosition;
		std::vector<Lane*> 					lanes;
		MainChar*							mainChar;

		SpriteNode*							boundHealthBar;
		SpriteNode*							healthBar;
    	TextNode* 							mHealthDisplay;
		State::Context 						mContext;

		sf::Clock							timeSinceLastDamage;
		const sf::Time						damageGap = sf::seconds(1);
};