#include <Application.hpp>

// Include all the state
#include <TitleState.hpp>
#include <MenuState.hpp>
#include <ChooseCharState.hpp>
#include <PauseState.hpp>
#include <GameState.hpp>
#include <SettingsState.hpp>
#include <LoginState.hpp>
#include <RegisterState.hpp>
#include <ConfirmRegisterState.hpp>
#include <DisplayCharState.hpp>
#include <GameOverState.hpp>
#include <ChooseWorldState.hpp>
#include <ChooseLevelState.hpp>
#include <VictoryState.hpp>
#include <ReturnGameState.hpp>
#include <CreditsState.hpp>
#include <ResetConfirm.hpp>
#include <ResetSuccess.hpp>

#include <fstream>
#include <exception>

const std::string Path_SaveAccount = "PrivateInfo/AccountSaving.txt";
const std::string tmp_Account = "PrivateInfo/TmpSaving.txt";

const std::string Path_MenuScreen = "Media/Textures/State/MenuScreen.png";
const std::string Path_TitleScreen = "Media/Textures/State/TitleScreen.png";
const std::string Path_Font = "Media/Font/slkscr.ttf";
const std::string Path_Input_Font = "Media/Font/Sansation.ttf";
const std::string Path_ChooseCharScreen = "Media/Textures/State/ChooseCharScreen.png";
const std::string Path_RightButton = "Media/Textures/Button/Right.png";
const std::string Path_LeftButton = "Media/Textures/Button/Left.png";
const std::string Path_Normal = "Media/Textures/Button/ButtonNormal.png";
const std::string Path_Pressed = "Media/Textures/Button/ButtonPressed.png";
const std::string Path_Selected = "Media/Textures/Button/ButtonSelected.png";
const std::string Path_InputButton = "Media/Textures/Button/purpleInputBox.png";
const std::string Path_loginBG = "Media/Textures/State/LoginBG.png";
const std::string Path_registerBG = "Media/Textures/State/RegisterBG.png";
const std::string Path_VisiblePassword = "Media/Textures/Button/visible.png";
const std::string Path_InvisiblePassword = "Media/Textures/Button/invisible.png";
const std::string Path_displayButton = "Media/Textures/Button/DisplayPlayer.png";
const std::string Path_heart = "Media/Textures/Icon/heart.png";
const std::string Path_Thunder = "Media/Textures/Icon/Thunder.png";
const std::string Path_registerButton = "Media/Textures/Button/RegisterButton.png";
const std::string Path_InputtButton = "Media/Textures/Button/InputButton.png";
const std::string Path_LoginButton = "Media/Textures/Button/loginButton.png";
const std::string Path_AcceptButton = "Media/Textures/Button/AcceptButton.png";
const std::string Path_InfoButton = "Media/Textures/Button/InfoButton.png";
const std::string Path_BackButton = "Media/Textures/Button/backButton.png";
const std::string Path_RegisterAccept = "Media/Textures/Button/RegisterAccept.png";
const std::string Path_SettingScreen = "Media/Textures/State/SettingScreen.png";
const std::string Path_ChooseWorldScreen = "Media/Textures/State/ChooseWorldScreen.png";
const std::string Path_ChooseWorldButton1 = "Media/Textures/Button/ThemeButton/Theme1/Country.png";
const std::string Path_ChooseWorldButton2 = "Media/Textures/Button/ThemeButton/Theme2/Snow.png";
const std::string Path_ChooseWorldButton3 = "Media/Textures/Button/ThemeButton/Theme3/Volcano.png";
const std::string Path_Theme1Screen = "Media/Textures/State/Theme/Theme1BG.png";
const std::string Path_Theme2Screen = "Media/Textures/State/Theme/Theme2BG.png";
const std::string Path_Theme3Screen = "Media/Textures/State/Theme/Theme3BG.png"; 
const std::string Path_Theme1NormalButton = "Media/Textures/Button/ThemeButton/Theme1/Normal.png";
const std::string Path_Theme1SelectedButton = "Media/Textures/Button/ThemeButton/Theme1/Selected.png";
const std::string Path_Theme1BackButton = "Media/Textures/Button/ThemeButton/Theme1/Back.png";
const std::string Path_Theme2NormalButton = "Media/Textures/Button/ThemeButton/Theme2/Normal.png";
const std::string Path_Theme2SelectedButton = "Media/Textures/Button/ThemeButton/Theme2/Selected.png";
const std::string Path_Theme2BackButton = "Media/Textures/Button/ThemeButton/Theme2/Back.png";
const std::string Paht_Theme3NormalButton = "Media/Textures/Button/ThemeButton/Theme3/Normal.png";
const std::string Path_Theme3SelectedButton = "Media/Textures/Button/ThemeButton/Theme3/Selected.png";
const std::string Path_Theme3BackButton = "Media/Textures/Button/ThemeButton/Theme3/Back.png";
const std::string Path_ThemeLv1Button = "Media/Textures/Button/ThemeButton/Lv1.png";
const std::string Path_ThemeLv2Button = "Media/Textures/Button/ThemeButton/Lv2.png";
const std::string Path_ThemeLv3Button = "Media/Textures/Button/ThemeButton/Lv3.png";
const std::string Path_ThemeLv4Button = "Media/Textures/Button/ThemeButton/Lv4.png";
const std::string Path_ThemeLv5Button = "Media/Textures/Button/ThemeButton/Lv5.png";
const std::string Path_VictoryIcon = "Media/Textures/State/VictoryIcon.png";
const std::string Path_VictoryMenuButton = "Media/Textures/Button/VictoryState/Menu.png";
const std::string Path_VictoryNextButton = "Media/Textures/Button/VictoryState/Next.png";
const std::string Path_VictoryPlayAgainButton = "Media/Textures/Button/VictoryState/PlayAgain.png";
const std::string Path_GameOverBG = "Media/Textures/State/GameOverBG.png";
const std::string Path_GameOverMenuButton = "Media/Textures/Button/GameOverState/Menu.png";
const std::string Path_GameOverPlayAgainButton = "Media/Textures/Button/GameOverState/PlayAgain.png";
const std::string Path_PauseBG = "Media/Textures/State/PauseBG.png";
const std::string Path_PauseResumeButton = "Media/Textures/Button/PauseState/Resume.png";
const std::string Path_PauseMenuButton = "Media/Textures/Button/PauseState/Menu.png";
const std::string Path_PauseSettingButton = "Media/Textures/Button/PauseState/Setting.png";
const std::string Path_NormalPauseButton = "Media/Textures/Button/PauseNormal.png";
const std::string Path_PressedPauseButton = "Media/Textures/Button/PausePressed.png";

// Application quite similar to the Game.cpp
const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
: mWindow(sf::VideoMode(1700, 950), "Game States (Beta Version) World", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mMusic()
, mSound()
, theme(0)
, limitLevel(15)
, curLevel(0)
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusic, mSound, theme, limitLevel, curLevel))
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
        mMusic.setVolume(10.f);
        mSound.setVolume(50.f);
        mStateStack.pushState(States::Title);

}

Application::~Application(){
    // Save User Info
    int curUID = mPlayer.getUID();
    if(curUID == 0)
        return;
    
    // Read Part
    std::ifstream fi(Path_SaveAccount);
    if(!fi.is_open()){
        // throw std::runtime_error("Application::~Application - Cannot open file " + Path_SaveAccount);
        return;
    }

    std::ofstream tmpFo(tmp_Account);
    if(!tmpFo.is_open()){
        // throw std::runtime_error("Application::~Application - Cannot open file " + tmp_Account);
        return;
    }

    int UID;
    std::string username;
    int passwordHash[5];
    int lv;
    while(fi >> UID >> username >> passwordHash[0] >> passwordHash[1] >> passwordHash[2] >> passwordHash[3] >> passwordHash[4] >> lv){
        if(UID == curUID)
            lv = limitLevel;
        tmpFo << UID << "\n" << username << "\n" << passwordHash[0] << " " << passwordHash[1] << " " << passwordHash[2] << " " << passwordHash[3] << " " << passwordHash[4] << "\n" << lv << "\n";
    }

    fi.close();
    tmpFo.close();

    // Write Part
    std::ifstream tmpFi(tmp_Account);
    if(!tmpFi.is_open()){
        // throw std::runtime_error("Application::~Application - Cannot open file " + tmp_Account);
        return;
    }

    std::ofstream fo(Path_SaveAccount);
    if(!fo.is_open()){
        // throw std::runtime_error("Application::~Application - Cannot open file " + Path_SaveAccount);
        return;
    }

    while(tmpFi >> UID >> username >> passwordHash[0] >> passwordHash[1] >> passwordHash[2] >> passwordHash[3] >> passwordHash[4] >> lv){
        fo << UID << "\n" << username << "\n" << passwordHash[0] << " " << passwordHash[1] << " " << passwordHash[2] << " " << passwordHash[3] << " " << passwordHash[4] << "\n" << lv << "\n";
    }

    tmpFi.close();
    fo.close();

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
    mStateStack.registerState<DisplayCharState>(States::DisplayCharState);
    mStateStack.registerState<GameOverState>(States::GameOver);
    mStateStack.registerState<ChooseWorldState>(States::ChooseWorldState);
    mStateStack.registerState<ChooseLevelState>(States::ChooseLevelState);
    mStateStack.registerState<VictoryState>(States::Victory);
    mStateStack.registerState<ReturnGameState>(States::ReturnGame);
    mStateStack.registerState<CreditsState>(States::Credits);
    mStateStack.registerState<ResetConfirmState>(States::ResetConfirm);
    mStateStack.registerState<ResetSuccessState>(States::ResetSuccess);
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
    mTextures.load(Textures::MenuScreen, Path_MenuScreen);
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
    mTextures.load(Textures::displayButton, Path_displayButton);
    mTextures.load(Textures::Heart, Path_heart);
    mTextures.load(Textures::Thunder, Path_Thunder);

    // Player
    mTextures.load(Textures::HealthBar, "Media/Textures/Player/HealthBar.png");
    mTextures.load(Textures::ManaBar, "Media/Textures/Player/ManaBar.png");
    mTextures.load(Textures::BoundBar, "Media/Textures/Player/BoundHPBar.png");
    mTextures.load(Textures::MoneyBar, "Media/Textures/Player/MoneyBar.png");

    // Player1
    mTextures.load(Textures::Standing1, "Media/Textures/Player/Player1/Standing.png");
    mTextures.load(Textures::Rest1, "Media/Textures/Player/Player1/Rest.png");
	mTextures.load(Textures::Up1, "Media/Textures/Player/Player1/Up.png");
	mTextures.load(Textures::Down1, "Media/Textures/Player/Player1/Down.png");
	mTextures.load(Textures::Left1, "Media/Textures/Player/Player1/Left.png");
	mTextures.load(Textures::Right1, "Media/Textures/Player/Player1/Right.png");

    // Player2
    mTextures.load(Textures::Standing2, "Media/Textures/Player/Player2/Standing.png");
    mTextures.load(Textures::Rest2, "Media/Textures/Player/Player2/Rest.png");
	mTextures.load(Textures::Up2, "Media/Textures/Player/Player2/Up.png");
	mTextures.load(Textures::Down2, "Media/Textures/Player/Player2/Down.png");
	mTextures.load(Textures::Left2, "Media/Textures/Player/Player2/Left.png");
	mTextures.load(Textures::Right2, "Media/Textures/Player/Player2/Right.png");
	mTextures.load(Textures::Healing, "Media/Textures/Player/Player2/Healing.png");
    
    // Player3
    mTextures.load(Textures::Standing3, "Media/Textures/Player/Player3/Standing.png");
    mTextures.load(Textures::Rest3, "Media/Textures/Player/Player3/Rest.png");
    mTextures.load(Textures::Up3, "Media/Textures/Player/Player3/Up.png");
    mTextures.load(Textures::Down3, "Media/Textures/Player/Player3/Down.png");
    mTextures.load(Textures::Left3, "Media/Textures/Player/Player3/Left.png");
    mTextures.load(Textures::Right3, "Media/Textures/Player/Player3/Right.png");
	mTextures.load(Textures::PowerShell, "Media/Textures/Player/Player3/PowerShell.png");
    
    // Player4
    mTextures.load(Textures::Standing4, "Media/Textures/Player/Player4/Standing.png");
    mTextures.load(Textures::Rest4, "Media/Textures/Player/Player4/Rest.png");
    mTextures.load(Textures::Up4, "Media/Textures/Player/Player4/Up.png");
    mTextures.load(Textures::Down4, "Media/Textures/Player/Player4/Down.png");
    mTextures.load(Textures::Left4, "Media/Textures/Player/Player4/Left.png");
    mTextures.load(Textures::Right4, "Media/Textures/Player/Player4/Right.png");

    // Player5
    mTextures.load(Textures::Standing5, "Media/Textures/Player/Player5/Standing.png");
    mTextures.load(Textures::Rest5, "Media/Textures/Player/Player5/Rest.png");
    mTextures.load(Textures::Up5, "Media/Textures/Player/Player5/Up.png");
    mTextures.load(Textures::Down5, "Media/Textures/Player/Player5/Down.png");
    mTextures.load(Textures::Left5, "Media/Textures/Player/Player5/Left.png");
    mTextures.load(Textures::Right5, "Media/Textures/Player/Player5/Right.png");
    
    // Road
    mTextures.load(Textures::Road, "Media/Textures/Road/Road.png");
	mTextures.load(Textures::LavaRoad, "Media/Textures/Road/LavaRoad.png");
    mTextures.load(Textures::SnowRoad, "Media/Textures/Road/SnowRoad.png");
	mTextures.load(Textures::Road1, "Media/Textures/Road/Road1.png");
	mTextures.load(Textures::Soil, "Media/Textures/Road/Soil.png");
    mTextures.load(Textures::IceRoad, "Media/Textures/Road/IceRoad.png");

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
    mTextures.load(Textures::Penguin1, "Media/Textures/Animal/Penguin.png");
    mTextures.load(Textures::Wolf, "Media/Textures/Animal/Wolf.png");

    mTextures.load(Textures::Traffic, "Media/Textures/Road/Traffic.png");
    mTextures.load(Textures::Truck, "Media/Textures/Vehicle/Truck.png");
    mTextures.load(Textures::Ambulance, "Media/Textures/Vehicle/Ambulance.png");
    mTextures.load(Textures::PoliceCar, "Media/Textures/Vehicle/PoliceCar.png");
    mTextures.load(Textures::SmallCar, "Media/Textures/Vehicle/SmallCar.png");
    mTextures.load(Textures::BlueCar, "Media/Textures/Vehicle/BlueCar.png");
    mTextures.load(Textures::YellowCar, "Media/Textures/Vehicle/YellowCar.png");
    mTextures.load(Textures::OldCar, "Media/Textures/Vehicle/OldCar.png");
    mTextures.load(Textures::SuperCar, "Media/Textures/Vehicle/SuperCar.png");
    mTextures.load(Textures::IceCreamTruck, "Media/Textures/Vehicle/IceCreamTruck.png");
    mTextures.load(Textures::SantaClaus, "Media/Textures/Vehicle/SantaClaus.png");

	// River
	mTextures.load(Textures::Log, "Media/Textures/River/Log.png");
	mTextures.load(Textures::Log1, "Media/Textures/River/Log1.png");
    mTextures.load(Textures::SnowLog1, "Media/Textures/River/SnowLog.png");
    mTextures.load(Textures::SnowLog2, "Media/Textures/River/SnowLog.png");
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
    mTextures.load(Textures::Coin, "Media/Textures/Obstacle/Coin.png");
	// Railway
	mTextures.load(Textures::Railway, "Media/Textures/Railway/Railway.png");
	mTextures.load(Textures::RailwayLight, "Media/Textures/Railway/RailwayLight.png");
    //mTextures.load(Textures::Traffic, "Media/Textures/Railway/Traffic.png");
    mTextures.load(Textures::Train1, "Media/Textures/Railway/Train1.png");
    mTextures.load(Textures::LavaTrain, "Media/Textures/Railway/LavaTrain.png");
    mTextures.load(Textures::SnowTrain, "Media/Textures/Railway/SnowTrain.png");
	mTextures.load(Textures::WoodTrain, "Media/Textures/Railway/WoodTrain.png");
    mTextures.load(Textures::SantaTrain, "Media/Textures/Railway/SantaTrain.png");
	// FinishLane
	mTextures.load(Textures::FinishLevel, "Media/Textures/FinishLane/LevelFinish.png");
	mTextures.load(Textures::FinishTheme1, "Media/Textures/FinishLane/FinishTheme1.png");
	mTextures.load(Textures::FinishTheme2, "Media/Textures/FinishLane/FinishTheme2.png");
    mTextures.load(Textures::FinishTheme3, "Media/Textures/FinishLane/FinishTheme3.png");

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


    // Special Button
    mTextures.load(Textures::PlayButton, "Media/Textures/Button/playButton.png");
    mTextures.load(Textures::SettingButton, "Media/Textures/Button/settingButton.png");
    mTextures.load(Textures::ExitButton, "Media/Textures/Button/exitButton.png");
    mTextures.load(Textures::LogoutButton, "Media/Textures/Button/logOutButton.png");
    mTextures.load(Textures::RegisterButton, Path_registerButton);
    mTextures.load(Textures::InputButton, Path_InputtButton);
    mTextures.load(Textures::LoginButton, Path_LoginButton);
    mTextures.load(Textures::AcceptButton, Path_AcceptButton);
    mTextures.load(Textures::InfoButton, Path_InfoButton);
    mTextures.load(Textures::BackButton, Path_BackButton);
    mTextures.load(Textures::RegisterAccept, Path_RegisterAccept);
    mTextures.load(Textures::SettingScreen, Path_SettingScreen);
    mTextures.load(Textures::ChooseWorldScreen, Path_ChooseWorldScreen);
    mTextures.load(Textures::World1, Path_ChooseWorldButton1);
    mTextures.load(Textures::World2, Path_ChooseWorldButton2);
    mTextures.load(Textures::World3, Path_ChooseWorldButton3);
    mTextures.load(Textures::Theme1Screen, Path_Theme1Screen);
    mTextures.load(Textures::Theme2Screen, Path_Theme2Screen);
    mTextures.load(Textures::Theme3Screen, Path_Theme3Screen);
    mTextures.load(Textures::Theme1NormalButton, Path_Theme1NormalButton);
    mTextures.load(Textures::Theme1SelectedButton, Path_Theme1SelectedButton);
    mTextures.load(Textures::Theme1BackButton, Path_Theme1BackButton);
    mTextures.load(Textures::Theme2NormalButton, Path_Theme2NormalButton);
    mTextures.load(Textures::Theme2SelectedButton, Path_Theme2SelectedButton);
    mTextures.load(Textures::Theme2BackButton, Path_Theme2BackButton);
    mTextures.load(Textures::Theme3NormalButton, Paht_Theme3NormalButton);
    mTextures.load(Textures::Theme3SelectedButton, Path_Theme3SelectedButton);
    mTextures.load(Textures::Theme3BackButton, Path_Theme3BackButton);
    mTextures.load(Textures::Level1, Path_ThemeLv1Button);
    mTextures.load(Textures::Level2, Path_ThemeLv2Button);
    mTextures.load(Textures::Level3, Path_ThemeLv3Button);
    mTextures.load(Textures::Level4, Path_ThemeLv4Button);
    mTextures.load(Textures::Level5, Path_ThemeLv5Button);
    mTextures.load(Textures::VictoryIcon, Path_VictoryIcon);
    mTextures.load(Textures::VictoryBackToMenuButton, Path_VictoryMenuButton);
    mTextures.load(Textures::VictoryNextLevelButton, Path_VictoryNextButton);
    mTextures.load(Textures::VictoryPlayAgainButton, Path_VictoryPlayAgainButton);
    mTextures.load(Textures::GameOverBG, Path_GameOverBG);
    mTextures.load(Textures::GameOverMenuButton, Path_GameOverMenuButton);
    mTextures.load(Textures::GameOverPlayAgainButton, Path_GameOverPlayAgainButton);
    mTextures.load(Textures::PauseBG, Path_PauseBG);
    mTextures.load(Textures::PauseResumeButton, Path_PauseResumeButton);
    mTextures.load(Textures::PauseMenuButton, Path_PauseMenuButton);
    mTextures.load(Textures::PauseSettingsButton, Path_PauseSettingButton);
    mTextures.load(Textures::NormalPauseButton, Path_NormalPauseButton);
    mTextures.load(Textures::PressedPauseButton, Path_PressedPauseButton);

    // Menu State Button
    mTextures.load(Textures::CreditButton, "Media/Textures/Button/Credit.png");
    mTextures.load(Textures::ResetButton, "Media/Textures/Button/Reset.png");

    // Reset Buttons
    mTextures.load(Textures::Cancle, "Media/Textures/Button/Resetting/Cancle.png");
    mTextures.load(Textures::Confirm, "Media/Textures/Button/Resetting/Confirm.png");
    mTextures.load(Textures::ResettingSuccessfully, "Media/Textures/Button/Resetting/ResettingSuccessfully.png");

    // Reset Screen
    mTextures.load(Textures::ResetConfirm, "Media/Textures/State/Reset/ResettingConfirm.png");
    mTextures.load(Textures::ResetSuccess, "Media/Textures/State/Reset/ResettingSuccess.png");

}
