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

		// Ground
		Ground,
		Grass,
		Soil,
		Obstacle,
		
		// Road
		Road,
		Road1,
		Elephant,
		Bird,
    	Rhinoceros,
		Cow,
		Small_Dragon,
    	Green_Dragon,
    	Red_Dragon,
    	Blue_Twin_Head_Dragon,

		Traffic,
        Truck,
        BlueCar,
        SmallCar,
        Ambulance,
        PoliceCar,
        SuperCar,
		YellowCar,
        OldCar,

		// Railway
		Railway,
		Train1,
		Train2,
		Train3,

		// Player
		Player1Up,
		Player1Down,
		Player1Left,
		Player1Right,
		Up1,
		Down1,
		Left1,
		Right1,
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