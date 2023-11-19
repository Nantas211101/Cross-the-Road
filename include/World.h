#pragma once

#include "TextureHolder.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Log.h"
#include "Lane.h"
#include "River.h"

#include <SFML/Graphics.hpp>

#include <memory>
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
		struct Data {
			const sf::Vector2f screenVelocity = sf::Vector2f(0.f, -50.f);
		};

	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;

		std::vector<Lane*>	rivers;
		const Data data;
};