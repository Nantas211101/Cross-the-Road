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
		// River
		River,
		Log,
		Ground,

		// Grass
		Grass,
		Tree,
		
		// Road
		Road,
		Road1,
		Elephant,
		Bird,
    	Rhinoceros,
		Small_Dragon,
    	Green_Dragon,
    	Red_Dragon,
    	Blue_Twin_Head_Dragon,

		Traffic,
		Truck,
		Car,

		// Player
		Chicken,
		Mallard,
		Penguin,
		Sheep,
		none
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