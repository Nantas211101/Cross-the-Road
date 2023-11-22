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
		Car
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