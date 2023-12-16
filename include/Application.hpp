#pragma once
#include <SFML/Graphics.hpp>
#include <StateStack.hpp>
#include <StateIdentifiers.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <StateIdentifiers.hpp>
#include <SoundPlayer.hpp>

// const std::string Path_MenuScreen = "resource/Textures/Menu.jpg";
// const std::string Path_WhiteBackground = "resource/Textures/WhiteBackground.jpg";
// const std::string Path_ButtonNormal = "resource/Textures/ButtonNormal.png";
// const std::string Path_ButtonSelected = "resource/Textures/ButtonSelected.png";
// const std::string Path_ButtonPressed = "resource/Textures/ButtonPressed.png";

class Application{

public:
    Application();
    void run();

private:
    void processInput();
    void update(sf::Time dt);
    void render();

private:
    void registerStates();
    void loadResources();
    void updateStatic(sf::Time dt);


private:
    static const sf::Time	TimePerFrame;

    sf::RenderWindow		mWindow;
    TextureHolder			mTextures;
    FontHolder				mFonts;
    Player                  mPlayer;
    
    MusicPlayer             mMusic;
    SoundPlayer             mSound;
    StateStack				mStateStack;

    sf::Text				mStayText;
    sf::Time				mStayUpdateTime;
    std::size_t				mStayNumFrames;
};