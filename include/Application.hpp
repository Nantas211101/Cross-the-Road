#pragma once
#include <SFML/Graphics.hpp>
#include <StateStack.hpp>
#include <StateIdentifiers.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <StateIdentifiers.hpp>
#include <SoundPlayer.hpp>
class Application{

public:
    Application();
    ~Application();

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
    int                     theme;
    int                     limitLevel;
    int                     curLevel;
    int                     curMoney;
    std::string             keyMoveUp;
    std::string             keyMoveDown;
    std::string             keyMoveLeft;
    std::string             keyMoveRight;
    std::string             keyUseAbility;
    int                     currentMusicVolume;
    int                     currentTotalVolume;
    StateStack				mStateStack;

    sf::Text				mStayText;
    sf::Time				mStayUpdateTime;
    std::size_t				mStayNumFrames;
};