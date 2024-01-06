#include <ResetSuccess.hpp>

#include <GUI_Button.hpp>
#include <ResourceIdentifiers.hpp>

namespace figmaPosition{
    const sf::Vector2f OKButtonPos = sf::Vector2f(850.f, 809.f);
}

ResetSuccessState::ResetSuccessState(StateStack& stack, Context context)
: State(stack, context)
, mBackground()
, mGUIContainer()
{
    mBackground.setTexture(context.textures->get(Textures::ResetSuccess));

    auto OKButton = std::make_shared<GUI::Button>(context, Textures::ResettingSuccessfully);
    OKButton->centerOrigin();
    OKButton->setPosition(figmaPosition::OKButtonPos);
    OKButton->setCallback([this](){
        requestStackPop();
    });

    mGUIContainer.pack(OKButton);
}

void ResetSuccessState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mGUIContainer);
}

bool ResetSuccessState::update(sf::Time dt){
    mElapsedTime += dt;
    return false;
}

bool ResetSuccessState::handleEvent(const sf::Event& event){
    if(mElapsedTime < sf::seconds(1.0))
        return false;
    sf::RenderWindow &mWindow = *getContext().window;
    mGUIContainer.handleRealTimeInput(mWindow);
    mGUIContainer.handleEvent(event);
    return false;
}

