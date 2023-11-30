#include "Application.hpp"

// Include all the state
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "ChooseCharState.hpp"
#include "PauseState.hpp"
#include "GameState.hpp"
#include "SettingsState.hpp"
#include "LoginState.hpp"

const std::string Path_TitleScreen = "Media/Textures/TitleScreen.jpg";
const std::string Path_Font = "Media/Font/slkscr.ttf";
const std::string Path_Input_Font = "Media/Font/Sansation.ttf";
const std::string Path_ChooseCharScreen = "Media/Textures/bluebackground.jpg";
const std::string Path_chickenMain = "Media/Textures/chicken.jpg";
const std::string Path_penguinMain = "Media/Textures/Penguin.png";
const std::string Path_sheepMain = "Media/Textures/Sheep.png";
const std::string Path_mallardMain = "Media/Textures/Mallard.png";
const std::string Path_RightButton = "Media/Textures/Right.png";
const std::string Path_LeftButton = "Media/Textures/Left.png";
const std::string Path_Normal = "Media/Textures/ButtonNormal.png";
const std::string Path_Pressed = "Media/Textures/ButtonPressed.png";
const std::string Path_Selected = "Media/Textures/ButtonSelected.png";
const std::string Path_InputButton = "Media/Textures/purpleInputBox.png";
const std::string Path_loginBG = "Media/Textures/LoginBG.jpg";
const std::string Path_registerBG = "Media/Textures/RegisterBG.jpg";
const std::string Path_VisiblePassword = "Media/Textures/visible.png";
const std::string Path_InvisiblePassword = "Media/Textures/invisible.png";

// Application quite similar to the Game.cpp
const sf::Time Application::TimePerFrame = sf::seconds(1.f / 120.f);

Application::Application()
: mWindow(sf::VideoMode(1920, 1080), "Game States (Beta Version) World", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
, mStayText()
, mStayUpdateTime()
, mStayNumFrames(0){
        // Not let the key repeat
        mWindow.setKeyRepeatEnabled(false);
        // mWindow.create()

        loadResources();

        // Set Font, position, and size for the text fps (this quite similar with the Game.hpp)
        mStayText.setFont(mFonts.get(Fonts::Main));
        mStayText.setPosition(5.f, 5.f);
        mStayText.setCharacterSize(10u);

        registerStates();
        // start with the title state
        mStateStack.pushState(States::Title);
}

void Application::registerStates(){
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<ChooseCharState>(States::ChooseChar);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<SettingsState>(States::Settings);
    mStateStack.registerState<LoginState>(States::Login);
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
    mTextures.load(Textures::chicken, Path_chickenMain);
    mTextures.load(Textures::penguin, Path_penguinMain);
    mTextures.load(Textures::sheep, Path_sheepMain);
    mTextures.load(Textures::mallard, Path_mallardMain);
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
}
