#pragma once 

#include "State.hpp"
#include "GUI_ContainerSET.hpp"

#include <SFML/Graphics.hpp>

class ResetConfirmState : public State{
public:
    ResetConfirmState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    void resetCurrentPlayerInfo();

private:
    sf::Sprite mBackground;
    GUI::ContainerSet mGUIContainer;
    sf::Time mElapsedTime;
};