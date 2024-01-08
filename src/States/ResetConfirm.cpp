#include <ResetConfirm.hpp>

#include <GUI_Button.hpp>
#include <ResourceIdentifiers.hpp>

namespace figmaPosition{
    const sf::Vector2f CancleButtonPos = sf::Vector2f(550.f, 809.f);
    const sf::Vector2f ConfirmButtonPos = sf::Vector2f(1150.f, 809.f);
};

ResetConfirmState::ResetConfirmState(StateStack& stack, Context context)
: State(stack, context)
, mBackground()
, mGUIContainer()
{
    mBackground.setTexture(context.textures->get(Textures::ResetConfirm));

    auto cancleButton = std::make_shared<GUI::Button>(context, Textures::Cancle);
    cancleButton->centerOrigin();
    cancleButton->setPosition(figmaPosition::CancleButtonPos);
    cancleButton->setCallback([this](){
        requestStackPop();
    });

    auto confirmButton = std::make_shared<GUI::Button>(context, Textures::Confirm);
    confirmButton->centerOrigin();
    confirmButton->setPosition(figmaPosition::ConfirmButtonPos);
    confirmButton->setCallback([this](){
        resetCurrentPlayerInfo();
        requestStackPop();
        requestStackPush(States::ResetSuccess);
    });

    mGUIContainer.pack(cancleButton);
    mGUIContainer.pack(confirmButton);
}

void ResetConfirmState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mGUIContainer);
}

bool ResetConfirmState::update(sf::Time dt){
    mElapsedTime += dt;
    return false;
}

bool ResetConfirmState::handleEvent(const sf::Event& event){

    if(mElapsedTime < sf::seconds(0.4))
        return false;
    sf::RenderWindow &mWindow = *getContext().window;
	mGUIContainer.handleRealTimeInput(mWindow);
    mGUIContainer.handleEvent(event);
    return false;
}

void ResetConfirmState::resetCurrentPlayerInfo(){
    *getContext().limitLevel = 1;
    *getContext().currentLevel = 1;
    *getContext().money = 0;
    getContext().player->setMaskID(1);
    *getContext().keyMoveUp = "Up";
    *getContext().keyMoveDown = "Down";
    *getContext().keyMoveLeft = "Left";
    *getContext().keyMoveRight = "Right";
    *getContext().keyUseAbility = "Space";
    *getContext().currentMusicVolume = 70;
    *getContext().currentTotalVolume = 70;
}