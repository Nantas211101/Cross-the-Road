#pragma once

#include "TextureHolder.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Log.h"
#include "Lane.h"
#include "River.h"
#include "Grass.h"
#include <SFML/Graphics.hpp>
#include "Tree.h"
#include <array>


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
			LayerCount
		};
		struct SpawnPoint {
			SpawnPoint(Log::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
			{}

			Log::Type type;
			float x;
			float y;
		};

	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;
		float								mScrollSpeed;

		std::vector<SpawnPoint>				mEnemySpawnPoints;
};