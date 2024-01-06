#pragma once 

#include <State.hpp>

class ReturnGameState : public State{
public:
    ReturnGameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    virtual void handleRealTimeInput();

private:
    void setNewText(const std::string& text);

private:
    sf::RectangleShape  mBackground;
    sf::Text            mText;
    sf::Time            mElapsedTime;
};