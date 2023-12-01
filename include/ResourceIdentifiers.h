#pragma once
// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

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
namespace Fonts
{
	enum ID
	{
		Main,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;