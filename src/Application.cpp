#include "Application.hpp"

// Include all the state
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "ChooseCharState.hpp"
#include "PauseState.hpp"
#include "GameState.hpp"
#include "SettingsState.hpp"
#include "LoginState.hpp"
#include "RegisterState.hpp"
#include "ConfirmRegisterState.hpp"
#include "DisplayCharState.hpp"

const std::string Path_TitleScreen = "Media/Textures/State/TitleScreen.jpg";
const std::string Path_Font = "Media/Font/slkscr.ttf";
const std::string Path_Input_Font = "Media/Font/Sansation.ttf";
const std::string Path_ChooseCharScreen = "Media/Textures/State/bluebackground.jpg";
const std::string Path_chickenMain = "Media/Textures/Player/Chicken.png";
const std::string Path_penguinMain = "Media/Textures/Player/Penguin.png";
const std::string Path_sheepMain = "Media/Textures/Player/Sheep.png";
const std::string Path_mallardMain = "Media/Textures/Player/Mallard.png";
const std::string Path_RightButton = "Media/Textures/Button/Right.png";
const std::string Path_LeftButton = "Media/Textures/Button/Left.png";
const std::string Path_Normal = "Media/Textures/Button/ButtonNormal.png";
const std::string Path_Pressed = "Media/Textures/Button/ButtonPressed.png";
const std::string Path_Selected = "Media/Textures/Button/ButtonSelected.png";
const std::string Path_InputButton = "Media/Textures/Button/purpleInputBox.png";
const std::string Path_loginBG = "Media/Textures/State/LoginBG.jpg";
const std::string Path_registerBG = "Media/Textures/State/RegisterBG.jpg";
const std::string Path_VisiblePassword = "Media/Textures/Button/visible.png";
const std::string Path_InvisiblePassword = "Media/Textures/Button/invisible.png";
const std::string Path_backButton = "Media/Textures/Button/backButton.png";
const std::string Path_displayButton = "Media/Textures/Button/DisplayPlayer.png";
const std::string Path_heart = "Media/Textures/Icon/heart.png";
const std::string Path_Thunder = "Media/Textures/Icon/Thunder.png";

// Application quite similar to the Game.cpp
const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
: mWindow(sf::VideoMode(1700, 950), "Game States (Beta Version) World", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mMusic()
, mSound()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusic, mSound))
, mStayText()
, mStayUpdateTime()
, mStayNumFrames(0){
        // Not let the key not repeat to help the input
        // mWindow.setKeyRepeatEnabled(false);
        // mWindow.create()

        loadResources();

        // Set Font, position, and size for the text fps (this quite similar with the Game.hpp)
        mStayText.setFont(mFonts.get(Fonts::Main));
        mStayText.setPosition(5.f, 5.f);
        mStayText.setCharacterSize(10u);

        registerStates();
        // start with the title state
        mStateStack.pushState(States::Title);

        mMusic.setVolume(25.f);
}

void Application::registerStates(){
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<ChooseCharState>(States::ChooseChar);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<SettingsState>(States::Settings);
    mStateStack.registerState<LoginState>(States::Login);
    mStateStack.registerState<RegisterState>(States::Register);
    mStateStack.registerState<ConfirmRegisterState>(States::ConfirmRegister);
    // mStateStack.registerState<DisplayCharState>(States::DisplayCharState);
}

void Application::processInput(){
    // Feeding events
    sf::Event event;
    while(mWindow.pollEvent(event)){
        mStateStack.handleEvent(event);

        if(mStateStack.isEmpty() || event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt){
    mStateStack.update(dt);
}

void Application::render(){
    mWindow.clear();
    mStateStack.draw();
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStayText);
    mWindow.display();
}

void Application::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen()){
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while(timeSinceLastUpdate > TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);

            // Maybe after update the stack will be empty
            if(mStateStack.isEmpty())
                mWindow.close();
        }

        updateStatic(elapsedTime);
        render();
    }
}

void Application::updateStatic(sf::Time elapsedTime){
    mStayUpdateTime += elapsedTime;
    mStayNumFrames += 1;

    if(mStayUpdateTime >= sf::seconds(1.0f)){
        mStayText.setString(
            "Frames / Second = " + toString(mStayNumFrames) + "\n" +
            // mStayNumFrames can be consider at Numofupdate
            "Time / Update = " + toString(mStayUpdateTime.asSeconds() / mStayNumFrames) + "us");
        // reset the mStay
        mStayUpdateTime -= sf::seconds(1.0f);
        mStayNumFrames = 0;
    }
}

void Application::loadResources(){
    mFonts.load(Fonts::Main, Path_Font);
    mFonts.load(Fonts::Label, Path_Input_Font);
    mTextures.load(Textures::TitleScreen, Path_TitleScreen);
    mTextures.load(Textures::ChooseCharScreen, Path_ChooseCharScreen);
    mTextures.load(Textures::Chicken, Path_chickenMain);
    mTextures.load(Textures::Penguin, Path_penguinMain);
    mTextures.load(Textures::Sheep, Path_sheepMain);
    mTextures.load(Textures::Mallard, Path_mallardMain);
    mTextures.load(Textures::RightButton, Path_RightButton);
    mTextures.load(Textures::LeftButton, Path_LeftButton);
    mTextures.load(Textures::ButtonNormal, Path_Normal);
    mTextures.load(Textures::ButtonPressed, Path_Pressed);
    mTextures.load(Textures::ButtonSelected, Path_Selected);
    mTextures.load(Textures::InputButton1, Path_InputButton);
    mTextures.load(Textures::LoginBG, Path_loginBG);
    mTextures.load(Textures::RegisterBG, Path_registerBG);
    mTextures.load(Textures::VisiblePassword, Path_VisiblePassword);
    mTextures.load(Textures::InvisiblePassword, Path_InvisiblePassword);
    mTextures.load(Textures::backButton, Path_backButton);
    mTextures.load(Textures::displayButton, Path_displayButton);
    mTextures.load(Textures::Heart, Path_heart);
    mTextures.load(Textures::Thunder, Path_Thunder);

    // Player1
    mTextures.load(Textures::Standing1, "Media/Textures/Player/Player1/Standing.png");
	mTextures.load(Textures::Up1, "Media/Textures/Player/Player1/Up.png");
	mTextures.load(Textures::Down1, "Media/Textures/Player/Player1/Down.png");
	mTextures.load(Textures::Left1, "Media/Textures/Player/Player1/Left.png");
	mTextures.load(Textures::Right1, "Media/Textures/Player/Player1/Right.png");

    // Player2
    mTextures.load(Textures::Standing2, "Media/Textures/Player/Player2/Standing.png");
	mTextures.load(Textures::Up2, "Media/Textures/Player/Player2/Up.png");
	mTextures.load(Textures::Down2, "Media/Textures/Player/Player2/Down.png");
	mTextures.load(Textures::Left2, "Media/Textures/Player/Player2/Left.png");
	mTextures.load(Textures::Right2, "Media/Textures/Player/Player2/Right.png");
    
    // Player3
    mTextures.load(Textures::Standing3, "Media/Textures/Player/Player3/Standing.png");
    mTextures.load(Textures::Up3, "Media/Textures/Player/Player3/Up.png");
    mTextures.load(Textures::Down3, "Media/Textures/Player/Player3/Down.png");
    mTextures.load(Textures::Left3, "Media/Textures/Player/Player3/Left.png");
    mTextures.load(Textures::Right3, "Media/Textures/Player/Player3/Right.png");

    // Road
    mTextures.load(Textures::Road, "Media/Textures/Road/Road.png");
	mTextures.load(Textures::LavaRoad, "Media/Textures/Road/LavaRoad.png");
    mTextures.load(Textures::SnowRoad, "Media/Textures/Road/SnowRoad.png");
	mTextures.load(Textures::Road1, "Media/Textures/Road/Road1.png");
	mTextures.load(Textures::Soil, "Media/Textures/Road/Soil.png");

    mTextures.load(Textures::Elephant, "Media/Textures/Animal/Elephant.png");
    mTextures.load(Textures::Rhinoceros, "Media/Textures/Animal/Rhinoceros.png");
	mTextures.load(Textures::Cow, "Media/Textures/Animal/Cow.png");
    mTextures.load(Textures::Small_Dragon, "Media/Textures/Animal/Small_Dragon.png");
    mTextures.load(Textures::Red_Dragon, "Media/Textures/Animal/Red_Dragon.png");
    mTextures.load(Textures::Green_Dragon, "Media/Textures/Animal/Green_Dragon.png");
    mTextures.load(Textures::Blue_Twin_Head_Dragon, "Media/Textures/Animal/Blue_Twin_Head_Dragon.png");
    mTextures.load(Textures::Monster1, "Media/Textures/Animal/Monster1.png");
    mTextures.load(Textures::Reindeer, "Media/Textures/Animal/Reindeer.png");
    mTextures.load(Textures::SnowBear, "Media/Textures/Animal/SnowBear.png");

    mTextures.load(Textures::Traffic, "Media/Textures/Road/Traffic.png");
    mTextures.load(Textures::Truck, "Media/Textures/Vehicle/Truck.png");
    mTextures.load(Textures::Ambulance, "Media/Textures/Vehicle/Ambulance.png");
    mTextures.load(Textures::PoliceCar, "Media/Textures/Vehicle/PoliceCar.png");
    mTextures.load(Textures::SmallCar, "Media/Textures/Vehicle/SmallCar.png");
    mTextures.load(Textures::BlueCar, "Media/Textures/Vehicle/BlueCar.png");
    mTextures.load(Textures::YellowCar, "Media/Textures/Vehicle/YellowCar.png");
    mTextures.load(Textures::OldCar, "Media/Textures/Vehicle/OldCar.png");
    mTextures.load(Textures::SuperCar, "Media/Textures/Vehicle/SuperCar.png");

	// River
	mTextures.load(Textures::Log, "Media/Textures/River/Log.png");
	mTextures.load(Textures::Log1, "Media/Textures/River/Log1.png");
    mTextures.load(Textures::SnowLog, "Media/Textures/River/SnowLog.png");
    mTextures.load(Textures::River, "Media/Textures/River/River.png");
	mTextures.load(Textures::LavaRiver, "Media/Textures/River/LavaRiver.png");
    mTextures.load(Textures::SnowRiver, "Media/Textures/River/SnowRiver.png");
    // mTextures.load(Textures::LavaRiver1, "Media/Textures/LavaRiver1.png");
	//mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png"); // crocodile

	// Ground
    mTextures.load(Textures::Grass, "Media/Textures/Ground/Grass.png");
	mTextures.load(Textures::LavaGround, "Media/Textures/Ground/LavaGround.png");
    mTextures.load(Textures::SnowGround, "Media/Textures/Ground/SnowGround.png");
	mTextures.load(Textures::LightGrass, "Media/Textures/Ground/LightGrass.png");
	mTextures.load(Textures::Tree1, "Media/Textures/Obstacle/Tree1.png");
	mTextures.load(Textures::Tree2, "Media/Textures/Obstacle/Tree2.png");
	mTextures.load(Textures::Tree3, "Media/Textures/Obstacle/Tree3.png");
    mTextures.load(Textures::SnowTree, "Media/Textures/Obstacle/SnowTree.png");
    mTextures.load(Textures::SnowTree1, "Media/Textures/Obstacle/SnowTree1.png");
	mTextures.load(Textures::Rock1, "Media/Textures/Obstacle/Rock1.png");
	mTextures.load(Textures::Rock2, "Media/Textures/Obstacle/Rock2.png");
	mTextures.load(Textures::Ruin1, "Media/Textures/Obstacle/Ruin1.png");
	mTextures.load(Textures::Ruin2, "Media/Textures/Obstacle/Ruin2.png");
	mTextures.load(Textures::Vocalno, "Media/Textures/Obstacle/Volcano.png");
	mTextures.load(Textures::Fire, "Media/Textures/Obstacle/Fire.png");
    mTextures.load(Textures::SnowMan, "Media/Textures/Obstacle/SnowMan.png");
	// Railway
	mTextures.load(Textures::Railway, "Media/Textures/Railway/Railway.png");
	mTextures.load(Textures::RailwayLight, "Media/Textures/Railway/RailwayLight.png");
    //mTextures.load(Textures::Traffic, "Media/Textures/Railway/Traffic.png");
    mTextures.load(Textures::Train1, "Media/Textures/Railway/Train1.png");
    mTextures.load(Textures::Train2, "Media/Textures/Railway/Train2.png");
    mTextures.load(Textures::Train3, "Media/Textures/Railway/Train3.png");
	mTextures.load(Textures::Train4, "Media/Textures/Railway/Train4.png");

	// FinishLane
	mTextures.load(Textures::FinishLevel, "Media/Textures/FinishLane/LevelFinish.png");
	mTextures.load(Textures::FinishTheme1, "Media/Textures/FinishLane/FinishTheme1.png");
	mTextures.load(Textures::FinishTheme2, "Media/Textures/FinishLane/FinishTheme2.png");

	//Decorator
	mTextures.load(Textures::DecoTree1, "Media/Textures/Decorator/DecoTree1.png");
	mTextures.load(Textures::DecoTree2, "Media/Textures/Decorator/DecoTree2.png");
	mTextures.load(Textures::DecoFlower1, "Media/Textures/Decorator/DecoFlower1.png");
    mTextures.load(Textures::DecoFlower2, "Media/Textures/Decorator/DecoFlower2.png");
    mTextures.load(Textures::DecoIce1, "Media/Textures/Decorator/DecoIce1.png");
    mTextures.load(Textures::DecoSnow1, "Media/Textures/Decorator/DecoSnow1.png");
    mTextures.load(Textures::DecoStone, "Media/Textures/Decorator/DecoStone.png");
    mTextures.load(Textures::Skullcap1, "Media/Textures/Decorator/Skullcap1.png");
    mTextures.load(Textures::Skullcap2, "Media/Textures/Decorator/Skullcap2.png");
    mTextures.load(Textures::DeadSign, "Media/Textures/Decorator/DeadSign.png");
    mTextures.load(Textures::Gemstone1, "Media/Textures/Decorator/Gemstone1.png");
    mTextures.load(Textures::Gemstone2, "Media/Textures/Decorator/Gemstone2.png");
    mTextures.load(Textures::Gemstone3, "Media/Textures/Decorator/Gemstone3.png");
}
