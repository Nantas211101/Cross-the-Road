#pragma once
// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
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
		HealthBar,
		BoundHealthBar,
		
		// Player1
		Standing1,
		Rest1,
		Up1,
		Down1,
		Left1,
		Right1,

		// Player2
		Standing2,
		Rest2,
		Up2,
		Down2,
		Left2,
		Right2,

		// Player3
		Standing3,
		Rest3,
		Up3,
		Down3,
		Left3,
		Right3,
		
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

namespace Music{
    enum ID{
        MenuTheme,
        ChooseCharTheme,
        GameTheme1,
        GameTheme2,
        GameTheme3,
    };
}

namespace SoundEffect{
	enum ID{
		Dead1,
		Dead2,
		Dead3,
		TouchTraffic,
		TouchTrain,
		TouchRiver,
		TouchTree,
		Button,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;