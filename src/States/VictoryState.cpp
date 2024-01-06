#include <VictoryState.hpp>

#include <Utility.hpp>
#include <GUI_Button.hpp>

#include <math.h>

namespace canvaPosition{
    const sf::Vector2f VictoryPos = sf::Vector2f(830, 391);
    const sf::Vector2f BackToMenuPos = sf::Vector2f(383.945, 828.5);
    const sf::Vector2f PlayAgainPos = sf::Vector2f(925.5, 828.5);
    const sf::Vector2f NextLevelPos = sf::Vector2f(1418, 828.5);
}

const int MaxLevel = 15;

const int themeLimit[3] = {
    5,
    10,
    15
};

VictoryState::VictoryState(StateStack& stack, Context context)
: State(stack, context)
, mBackground()
, mVictorySprite()
, mGUIContainer()
{
    // Win and increase the limit level

    int& curLevel = *context.currentLevel;
    int& limitLevel = *context.limitLevel;
    int& theme = *context.theme;

    limitLevel = std::max(limitLevel, curLevel + 1);
    curLevel = std::min(curLevel + 1, MaxLevel);

    if(curLevel > themeLimit[theme - 1])
        ++theme;

    setNewMask(limitLevel);

    //

    mBackground.setSize(sf::Vector2f(context.window->getView().getSize()));
    mBackground.setFillColor(sf::Color(0, 0, 0, 200));

    sf::Texture& textures = context.textures->get(Textures::VictoryIcon);
    mVictorySprite.setTexture(textures);
    mVictorySprite.setPosition(canvaPosition::VictoryPos);
    centerOrigin(mVictorySprite);

    auto backToMenuButton = std::make_shared<GUI::Button>(context, Textures::VictoryBackToMenuButton);
    backToMenuButton->centerOrigin();
    backToMenuButton->setPosition(canvaPosition::BackToMenuPos);
    backToMenuButton->setCallback([this](){
        requestStateClear();
        requestStackPush(States::Menu);
    });

    auto playAgainButton = std::make_shared<GUI::Button>(context, Textures::VictoryPlayAgainButton);
    playAgainButton->centerOrigin();    
    playAgainButton->setPosition(canvaPosition::PlayAgainPos);
    playAgainButton->setCallback([this](){
        requestStateClear();
        requestStackPush(States::Game);
    });

    auto nextLevelButton = std::make_shared<GUI::Button>(context, Textures::VictoryNextLevelButton);
    nextLevelButton->centerOrigin();
    nextLevelButton->setPosition(canvaPosition::NextLevelPos);
    nextLevelButton->setCallback([this](){
        requestStateClear();
        requestStackPush(States::Game);
    });

    mGUIContainer.pack(backToMenuButton);
    mGUIContainer.pack(playAgainButton);
    mGUIContainer.pack(nextLevelButton);
}

void VictoryState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mVictorySprite);
    window.draw(mGUIContainer);
}

bool VictoryState::update(sf::Time dt)
{
    mElapsedTime += dt;
    mGUIContainer.update(dt);
    return false;
}

bool VictoryState::handleEvent(const sf::Event& event)
{

    if(mElapsedTime < sf::seconds(1.0))
        return false;
    sf::RenderWindow& window = *getContext().window;
    mGUIContainer.handleRealTimeInput(window);
    mGUIContainer.handleEvent(event);
    return false;
}

void VictoryState::handleRealTimeInput()
{

}

void VictoryState::setNewMask(int lv){
    int newMask = convertFromLevelToMaskID(lv);
    getContext().player->setMaskID(newMask);
}