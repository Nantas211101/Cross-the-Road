#pragma once 

#include <State.hpp>
#include <ResourceIdentifiers.hpp>
#include <TextureManipulate.hpp>
#include <GUI_Container.hpp>

#include <SFML/Graphics.hpp>

class ChooseWorldState : public State{
public:
    ChooseWorldState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    virtual void handleRealTimeInput();

private:
    sf::Sprite mBackgroundSprite;
    GUI::Container mGUIContainer;

    sf::Time mElapsedTime;
};