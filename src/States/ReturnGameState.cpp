#include "ReturnGameState.hpp"
#include <Utility.hpp>

const float scaleBig = 1.1;

ReturnGameState::ReturnGameState(StateStack& stack, Context context)
: State(stack, context)
, mBackground()
, mText("3", context.fonts->get(Fonts::Main), 300)
, mElapsedTime(sf::Time::Zero)
{
    sf::Vector2f pos = context.window->getView().getCenter();
    mBackground.setFillColor(sf::Color(0, 0, 0, 150));
    mBackground.setSize(sf::Vector2f(context.window->getSize()));
    mText.setFillColor(sf::Color::White);
    centerOrigin(mText);
    mText.setPosition(pos);
}

void ReturnGameState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mText);
}

bool ReturnGameState::update(sf::Time dt){
    mElapsedTime += dt;
    int num = 4;
    float elapsedTime = mElapsedTime.asSeconds();
    mText.setScale(elapsedTime * scaleBig, elapsedTime * scaleBig);
    if(elapsedTime >= 1.f){
        const std::string& text = mText.getString();
        if(text == "GO!"){
            requestStackPop();
            return false;
        }
        num = toInt(text);
        --num;
        setNewText(toString(num));
        mElapsedTime -= sf::seconds(1.f);
    }

    if(num == 0){
        setNewText("GO!");
    }
    return false;
}

bool ReturnGameState::handleEvent(const sf::Event& event){
    return false;
}

void ReturnGameState::handleRealTimeInput(){
    return;
}

void ReturnGameState::setNewText(const std::string& text){
    sf::Vector2f pos = mText.getPosition();
    mText.setScale(1, 1);
    mText.setString(text);
    centerOrigin(mText);
    mText.setPosition(pos);
}