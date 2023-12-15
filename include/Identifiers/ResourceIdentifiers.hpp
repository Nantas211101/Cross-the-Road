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
		LavaRiver,
		Log,
		Log1,

		// Ground
		Ground,
		Grass,
		LavaGround,
		LightGrass,
		Tree1,
		Tree2,
		Tree3,
		Rock1,
		Rock2,
		Ruin1,
		Ruin2,
		Vocalno,
		Fire,
		// Road
		Road,
		Road1,
		LavaRoad,
		Soil,
		Elephant,
		Bird,
    	Rhinoceros,
		Cow,
		Small_Dragon,
    	Green_Dragon,
    	Red_Dragon,
    	Blue_Twin_Head_Dragon,
		Monster1,

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
		RailwayLight,
		Train1,
		Train2,
		Train3,
		Train4,

		// FinishLane
		FinishLevel1,
		FinishLevel2,
		FinishLevel3,
		FinishTheme1,
		FinishTheme2,


		//Decorator
		DecoTree1,
		DecoTree2,
		DecoFlower1,
        DecoRock1,
		DecoRock2,
		DecoFire1,
		DecoFire2,
		
		// Player
		Standing1,
		Up1,
		Down1,
		Left1,
		Right1,
		Chicken,
		Mallard,
		Penguin,
		Sheep,
		none,

		// Menu and State part
		background,
        TitleScreen,
        ChooseCharScreen,
        RightButton,
        LeftButton,
        ButtonNormal,
        ButtonPressed,
        ButtonSelected,
        InputButton1,
        LoginBG,
        RegisterBG,
        VisiblePassword,
        InvisiblePassword,
        backButton,
        displayButton,
        
        Heart,
        Thunder,
	};
}
namespace Fonts
{
	enum ID
	{
		Main,
		Label,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;