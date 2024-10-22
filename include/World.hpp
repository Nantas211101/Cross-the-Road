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
		enum InGameState {
			Win,
			Lose,
			Playing,
		};
	public:
		explicit		 					World(State::Context context);
		void								update(sf::Time dt);
		void								draw();
		CommandQueue&						getCommandQueue();
		InGameState							getInGameState();
		int									getMoney();

	private:
		void								buildScene(MainChar::Type id);
		void 								adaptPlayerPosition();
		void								handleCollisions();
		void								scroll(sf::Time dt);
		void								buildHealthBar();
		void								updateHealthBar();
		void								buildMap();	
		void								updateMana(sf::Time dt);
		void								buildMainChar();
		void								updateSound();
		void								buildMoneyInFo();
		void								updateMoneyBar();

	private:
		enum Layer
		{
			Background,
			Title,
			AboveTitle,
			LayerCount
		};
	private:
		State::Context 						mContext;
		InGameState							playingState;
		int									money;

		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		sf::FloatRect						mWorldBounds;
		TextureHolder&						mTextures;
		FontHolder&							mFonts;
		SoundPlayer&						mSound;

		const float							scrollSpeed = -200.f;
		float								scrollSpeedToPlayer = -50.f;
		float								scrollDistance;
		int									playerLaneIndex;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;
		CommandQueue						soundCommandQueue;

		sf::Vector2f						mSpawnPosition;
		std::vector<Lane*> 					lanes;
		MainChar*							mainChar;

		SpriteNode*							moneyBar;
		TextNode*							moneyDisplay;

		SpriteNode*							boundBar;
		SpriteNode*							healthBar;
		SpriteNode*							manaBar;
    	TextNode* 							mHealthDisplay;
		int									highestBound;
		const sf::Time						timeEachAddMana = sf::seconds(0.2);
		sf::Time							timeSinceLastAddMana;

		sf::Clock							timeSinceLastDamage;
		const sf::Time						damageGap = sf::seconds(1);
		sf::Clock							timeSinceLastDamageByRiver;
		const sf::Time						damageGapByRiver = sf::seconds(0.1);
		sf::Clock							timeRiverSound;
		const sf::Time						riverSoundGap = sf::seconds(4);
};