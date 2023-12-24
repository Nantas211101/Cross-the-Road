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
		SnowRiver,
		Log,
		Log1,
		SnowLog,
		
		// Ground
		Ground,
		Grass,
		LavaGround,
		SnowGround,
		LightGrass,
		Tree1,
		Tree2,
		Tree3,
		SnowTree,
		SnowTree1,
		Rock1,
		Rock2,
		Ruin1,
		Ruin2,
		Vocalno,
		Fire,
		SnowMan,
		// Road
		Road,
		Road1,
		LavaRoad,
		SnowRoad,
		IceRoad,
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
		Reindeer,
		SnowBear,

		Traffic,
        Truck,
        BlueCar,
        SmallCar,
        Ambulance,
        PoliceCar,
        SuperCar,
		YellowCar,
        OldCar,
		IceCreamTruck,
		SantaClaus,

		// Railway
		Railway,
		RailwayLight,
		Train1,
		SnowTrain,
		WoodTrain,
		LavaTrain,
		SantaTrain,

		// FinishLane
		FinishLevel,
		FinishTheme1,
		FinishTheme2,
		FinishTheme3,


		//Decorator
		DecoTree1,
		DecoTree2,
		DecoStone,
		DecoFlower1,
		DecoFlower2,
		DecoSnow1,
		DecoIce1,
		DeadSign,
		Skullcap1,
		Skullcap2,
        DecoRock1,
		DecoRock2,
		DecoFire1,
		DecoFire2,
		Gemstone1,
		Gemstone2,
		Gemstone3,

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
		
		// Player4
		Standing4,
		Rest4,
		Up4,
		Down4,
		Left4,
		Right4,

		// Player4
		Standing5,
		Rest5,
		Up5,
		Down5,
		Left5,
		Right5,

		Chicken,
		Mallard,
		Penguin,
		Sheep,
		none,

		// Menu and State part
		background,
        TitleScreen,
        ChooseCharScreen,
		SettingScreen,
		MenuScreen,
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
        displayButton,

		// Special button
		PlayButton,
		SettingButton,
		ExitButton,
		LogoutButton,
		RegisterButton,
		InputButton,
		LoginButton,
		AcceptButton, 
		InfoButton,
		BackButton,
		RegisterAccept,
        
        Heart,
        Thunder,

		// Choose World 
		World1,
		World2,
		World3,

		ChooseWorldScreen,

		// Choose Level Screen
		Theme1Screen,
		Theme2Screen,
		Theme3Screen,

		// Theme 1 button
		Theme1NormalButton,
		Theme1SelectedButton,
		Theme1BackButton,

		// Theme 2 button
		Theme2NormalButton,
		Theme2SelectedButton,
		Theme2BackButton,

		// Theme 3 button
		Theme3NormalButton,
		Theme3SelectedButton,
		Theme3BackButton,

		// Level Texture
		Level1,
		Level2,
		Level3,
		Level4,
		Level5,

		// Victory State		
		VictoryIcon,
		VictoryPlayAgainButton,
		VictoryNextLevelButton,
		VictoryBackToMenuButton,

		// GameOver State
		GameOverBG,
		GameOverMenuButton,
		GameOverPlayAgainButton,

		// Pause State
		PauseBG,
		PauseResumeButton,
		PauseMenuButton,
		PauseSettingsButton,

		// Support Pause Button
		NormalPauseButton,
		PressedPauseButton,

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
		None,
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