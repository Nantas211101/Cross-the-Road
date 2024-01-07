#pragma once 

#include "State.hpp"
#include "GUI_ContainerSET.hpp"

#include <SFML/Graphics.hpp>

class PurchaseConfirmState : public State{
public:
    PurchaseConfirmState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    bool purchasing();

private:
    sf::Sprite mBackground;
    GUI::ContainerSet mGUIContainer;
    sf::Time mElapsedTime;
};