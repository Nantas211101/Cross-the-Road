#pragma once
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "GUI_Container.hpp"
#include "GUI_ContainerSET.hpp"
#include "ResourceHolder.hpp"

#include <string>

class RegisterState : public State{
public: 
    RegisterState(StateStack &stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);
    virtual void handleRealTimeInput();

private:
    GUI::Container mGUIContainer;
    sf::Sprite mBackground;

    sf::Text mText;
    sf::Text errorText;
    std::string mTextUsername;
    std::string mTextPassword;

};