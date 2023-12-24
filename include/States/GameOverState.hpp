#pragma once

#include <State.hpp>
#include <ResourceIdentifiers.hpp>
#include <TextureManipulate.hpp>
#include <GUI_ContainerSET.hpp>

#include <SFML/Graphics.hpp>

class GameOverState : public State{
public:
    GameOverState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    virtual void handleRealTimeInput();

private:
    sf::RectangleShape mBackground;
    sf::Sprite mGameOverSprite;
    GUI::ContainerSet mGUIContainer;
};