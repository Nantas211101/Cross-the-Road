#pragma once 

#include <State.hpp>
#include <ResourceIdentifiers.hpp>
#include <TextureManipulate.hpp>
#include <GUI_Container.hpp>

#include <SFML/Graphics.hpp>

class VictoryState : public State{
public:
    VictoryState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    virtual void handleRealTimeInput();

private:
    void setNewMask(int lv);
    void setNewLevel();

private:
    sf::RectangleShape mBackground;
    sf::Sprite mVictorySprite;
    GUI::Container mGUIContainer;
    sf::Time mElapsedTime;

    bool isEndGame;
};