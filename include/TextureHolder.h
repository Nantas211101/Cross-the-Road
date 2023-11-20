#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <SFML/Graphics.hpp>

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Desert,
		
		River,
		Log,
		Ground,

		Grass,
		Tree,
		
		Road,
		Elephant,
		Bird, 
        Buffalo,
        Hippo,
        Rhinoceros
	};
}

class TextureHolder
{
	public:
		void load(Textures::ID id, const std::string& filename);
		sf::Texture& get(Textures::ID id);
		const sf::Texture& get(Textures::ID id) const;

	private:
		void insertResource(Textures::ID id, std::unique_ptr<sf::Texture> resource);

	private:
		std::map<Textures::ID, std::unique_ptr<sf::Texture>> mResourceMap;
};