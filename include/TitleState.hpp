#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "ResourceIdentifiers.hpp"
#include "TextureManipulate.hpp"

class TitleState : public State{
public:
    TitleState(StateStack &stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);
    virtual void handleRealTimeInput();

private:
    sf::Sprite mBackgroundSprite;
    sf::Text mText;
    sf::Text mDirectorText;
    sf::Text mProjectText;
    bool isShowText;
    bool isFocus;
    sf::Time mTextTimeEffected;
};