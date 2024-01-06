#pragma once
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "GUI_Container.hpp"
#include "GUI_ContainerSET.hpp"

#include <string>

class ConfirmRegisterState : public State{
public:
    ConfirmRegisterState(StateStack &stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);

private:
    virtual void handleRealTimeInput();

private:
    GUI::Container mGUIContainer;
    sf::RectangleShape mBackground;

    sf::Text mText;
    sf::Time mElapsedTime;
};