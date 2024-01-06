#include "PauseState.hpp"

#include "ResourceIdentifiers.hpp"
#include "TextureManipulate.hpp"
#include <GUI_Button.hpp>

namespace canvaPosition{
    const sf::Vector2f PauseBGPos = sf::Vector2f(831, 466.5);
    const sf::Vector2f MenuButtonPos = sf::Vector2f(531, 522);
    const sf::Vector2f ResumeButtonPos = sf::Vector2f(840.5, 526);
    const sf::Vector2f SettingsButtonPos = sf::Vector2f(1122.5, 526);
}

PauseState::PauseState(StateStack &stack, Context context)
: State(stack, context)
, mBackground()
, mPausedSprite()
, mGUIContainer()
{
    // mBackgroundSprite quite useless with PauseState
    sf::Font &font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize(); // get the size of the view

    // create background 
    mBackground.setFillColor(sf::Color(0, 0, 0, 150));
    mBackground.setSize(sf::Vector2f(context.window->getSize()));

    mPausedSprite.setTexture(context.textures->get(Textures::PauseBG));
    mPausedSprite.setPosition(canvaPosition::PauseBGPos);
    centerOrigin(mPausedSprite);

    auto menuButton = std::make_shared<GUI::Button>(context, Textures::PauseMenuButton);
    menuButton->centerOrigin();
    menuButton->setPosition(canvaPosition::MenuButtonPos);
    menuButton->setCallback([this](){
        requestStateClear();
        requestStackPush(States::Menu);
    });

    auto resumeButton = std::make_shared<GUI::Button>(context, Textures::PauseResumeButton);
    resumeButton->centerOrigin();
    resumeButton->setPosition(canvaPosition::ResumeButtonPos);
    resumeButton->setCallback([this](){
        requestStackPop();
        requestStackPush(States::ReturnGame);
    });

    auto settingsButton = std::make_shared<GUI::Button>(context, Textures::PauseSettingsButton);
    settingsButton->centerOrigin();
    settingsButton->setPosition(canvaPosition::SettingsButtonPos);
    settingsButton->setCallback([this](){
        requestStackPush(States::Settings);
    });

    mGUIContainer.pack(menuButton);
    mGUIContainer.pack(resumeButton);
    mGUIContainer.pack(settingsButton);
    context.music->setPaused(true); // pause the music
}

PauseState::~PauseState()
{
    getContext().music->setPaused(false); // resume the music
}

void PauseState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mPausedSprite);
    window.draw(mGUIContainer);
}

bool PauseState::update(sf::Time dt){
    mElapsedTime += dt;
    mGUIContainer.update(dt);
    return false;
}

bool PauseState::handleEvent(const sf::Event &event){
    if(mElapsedTime < sf::seconds(1.0))
        return false;
    sf::RenderWindow& window = *getContext().window;
    mGUIContainer.handleRealTimeInput(window);
    mGUIContainer.handleEvent(event);
    return false;
}