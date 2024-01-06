#include <GameOverState.hpp>

#include <GUI_Button.hpp>

const sf::Time TextEffectedTime[2] = {sf::seconds(0.3f), sf::seconds(0.5f)};

namespace canvaPosition{
    const sf::Vector2f GameOverBGPos = sf::Vector2f(850, 445);
    const sf::Vector2f MenuButtonPos = sf::Vector2f(515.5, 588.5);
    const sf::Vector2f PlayAgainButtonPos = sf::Vector2f(1152.5, 588.5);
}

GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mBackground()
, mGameOverSprite()
, mGUIContainer()
{
    mBackground.setFillColor(sf::Color(0, 0, 0, 200));
    mBackground.setSize(sf::Vector2f(context.window->getSize()));

    mGameOverSprite.setTexture(context.textures->get(Textures::GameOverBG));
    mGameOverSprite.setPosition(canvaPosition::GameOverBGPos);
    centerOrigin(mGameOverSprite);

    auto menuButton = std::make_shared<GUI::Button>(context, Textures::GameOverMenuButton);
    menuButton->centerOrigin();
    menuButton->setPosition(canvaPosition::MenuButtonPos);
    menuButton->setCallback([this](){
        requestStateClear();
        requestStackPush(States::Menu);
    });

    auto playAgainButton = std::make_shared<GUI::Button>(context, Textures::GameOverPlayAgainButton);
    playAgainButton->centerOrigin();
    playAgainButton->setPosition(canvaPosition::PlayAgainButtonPos);
    playAgainButton->setCallback([this](){
        requestStateClear();
        requestStackPush(States::Game);
    });

    mGUIContainer.pack(menuButton);
    mGUIContainer.pack(playAgainButton);
}

void GameOverState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mGameOverSprite);
    window.draw(mGUIContainer);
}

bool GameOverState::update(sf::Time dt){
    mElapsedTime += dt;
    mGUIContainer.update(dt);    
    return false;
}

bool GameOverState::handleEvent(const sf::Event &event){
    if(mElapsedTime < sf::seconds(1.0))
        return false;
    sf::RenderWindow& window = *getContext().window;
    mGUIContainer.handleRealTimeInput(window);
    mGUIContainer.handleEvent(event);
    return false;
}

void GameOverState::handleRealTimeInput(){

}
