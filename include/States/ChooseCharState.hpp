#pragma once
#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <SceneNode.hpp>
#include <MainChar.hpp>
// #include "GUI_Container.hpp"
#include "GUI_ContainerSET.hpp"

#include <array>


class ChooseCharState : public State{
public:
    ChooseCharState(StateStack &stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);
    virtual void handleRealTimeInput();

private:
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void impleChangeChar(sf::Time dt);
    void changeRight(sf::Time dt);
    void changeLeft(sf::Time dt);
    void startRight();
    void startLeft();
    
private:
    void buildScene();
    void createMainChar();

private:
    void PlayGame();

    void callError(const std::string& error);

    void updateCharID();


private:
    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

private:
    sf::View mWorldView;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    
    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;

    MainChar* mPlayer;
    MainChar* tmpPlayer;
    bool 								isMove;
    bool 								isPressing;
    bool 								isChange;
    sf::Keyboard::Key 					isChangeKey;

    bool isFocus;
    std::string name;

    // GUI::Container mGUIContainer;
    GUI::ContainerSet mGUIContainerSet;

    int maskID;
    sf::Text uidDisplay;
    sf::Text ErrorText;
    
    sf::Time mElapsedTime;
};

// static bool isCharacterMove = false;