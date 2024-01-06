#include <ChooseWorldState.hpp>

#include <GUI_Button.hpp>

namespace canvaPosition{
    const sf::Vector2f backButtonPos = sf::Vector2f(228.5, 846);
    const sf::Vector2f world1Pos = sf::Vector2f(296.5, 499);
    const sf::Vector2f world2Pos = sf::Vector2f(850, 598);
    const sf::Vector2f world3Pos = sf::Vector2f(1403.5, 499);
}

ChooseWorldState::ChooseWorldState(StateStack& stack, Context context)
: State(stack, context)
, mBackgroundSprite()
, mGUIContainer()
{
    sf::Texture& textures = context.textures->get(Textures::ChooseWorldScreen);
    mBackgroundSprite.setTexture(textures);

    auto backButton = std::make_shared<GUI::Button>(context, Textures::BackButton);
    backButton->centerOrigin();
    backButton->setPosition(canvaPosition::backButtonPos);
    backButton->setCallback([this](){
        requestStackPop();
        requestStackPush(States::Menu);
    });

    auto world1Button = std::make_shared<GUI::Button>(context, Textures::World1);
    world1Button->centerOrigin();
    world1Button->setPosition(canvaPosition::world1Pos);
    world1Button->setCallback([this](){
        *getContext().theme = 1;
        requestStackPop();
        requestStackPush(States::ChooseLevelState);
    });

    auto world2Button = std::make_shared<GUI::Button>(context, Textures::World2);
    world2Button->centerOrigin();
    world2Button->setPosition(canvaPosition::world2Pos);
    world2Button->setCallback([this](){
        *getContext().theme = 2;
        requestStackPop();
        requestStackPush(States::ChooseLevelState);
    });

    auto world3Button = std::make_shared<GUI::Button>(context, Textures::World3);
    world3Button->centerOrigin();
    world3Button->setPosition(canvaPosition::world3Pos);
    world3Button->setCallback([this](){
        *getContext().theme = 3;
        requestStackPop();
        requestStackPush(States::ChooseLevelState);
    });

    mGUIContainer.pack(world1Button);
    mGUIContainer.pack(world2Button);
    mGUIContainer.pack(world3Button);
    mGUIContainer.pack(backButton);
}

void ChooseWorldState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

bool ChooseWorldState::update(sf::Time dt)
{
    mElapsedTime += dt;
    mGUIContainer.update(dt);
    return true;
}

bool ChooseWorldState::handleEvent(const sf::Event& event)
{
    if(mElapsedTime < sf::seconds(1.0))
        return false;
    sf::RenderWindow& window = *getContext().window;
    mGUIContainer.handleRealTimeInput(window);
    mGUIContainer.handleEvent(event);
    return false;
}

void ChooseWorldState::handleRealTimeInput()
{

}