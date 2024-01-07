#pragma once

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <SceneNode.hpp>
#include <MainChar.hpp>
#include <GUI_ContainerSET.hpp>
#include <TextNode.hpp>

#include <array>

class DisplayCharState : public State{
public:
    DisplayCharState(StateStack &stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);
    virtual void handleRealTimeInput();

// private:
//     void startRight();
//     void endLeft();

private:
    void buildScene(Context context);
    void createMainChar(Context context);

private:
    enum Layer
    {
        Background,
        Moving,
        LayerCount
    };

private:
    sf::Text mText;
    sf::View mWorldView;
    SceneNode mSceneGraph;
    MainChar* mPlayer;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    sf::FloatRect hpRect;
    sf::FloatRect speedRect;

    sf::RectangleShape hpBarBackground;
    sf::RectangleShape speedBarBackground;
    sf::RectangleShape hpBar;
    sf::RectangleShape speedBar;
    sf::RectangleShape mBackground;
    
    sf::IntRect hpTextureRect;
    sf::IntRect speedTextureRect;

    sf::Sprite HP;
    sf::Sprite Speed;
    sf::Text HPText;
    sf::Text SpeedText;
    sf::Text AbilityText;

    TextNode* mTextMove;

    GUI::ContainerSet mGUIContainerSet;

    sf::Sprite mMoneyBar;
    sf::Text mMoneyText;

    sf::Time mElapsedTime;
    int maskID;
};