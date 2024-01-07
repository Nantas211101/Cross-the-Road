#pragma once  

#include <State.hpp>

#include <vector>

class CreditsState : public State{
public:
    CreditsState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    virtual void handleRealTimeInput();

private:
    void setNewText(const std::string& text, const int& cnt, const sf::Font& font, unsigned int size, const sf::Color& color = sf::Color::White);

private:
    sf::View            mWorldView;
    sf::FloatRect       mWorldBounds;
    std::vector<sf::Text> mTexts;
    sf::Vector2f        mSpawnPosition;
    sf::Text            mText;
    sf::Text            mInstructionText;
    sf::Time            mElapsedTime;
    
};