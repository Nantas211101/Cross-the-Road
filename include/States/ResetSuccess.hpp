#pragma once 

#include "State.hpp"
#include "GUI_ContainerSET.hpp"

#include <SFML/Graphics.hpp>

class ResetSuccessState : public State{
public:
    ResetSuccessState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Sprite mBackground;
    GUI::ContainerSet mGUIContainer;
    sf::Time mElapsedTime;
};