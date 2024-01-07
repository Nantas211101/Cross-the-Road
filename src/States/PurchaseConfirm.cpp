#include <PurchaseConfirm.hpp>

#include <GUI_Button.hpp>
#include <ResourceIdentifiers.hpp>
#include <iostream>

namespace figmaPosition{
    const sf::Vector2f BackGroundPos = sf::Vector2f(457, 244);
    const sf::Vector2f CancleButtonPos = sf::Vector2f(675.5, 594);
    const sf::Vector2f ConfirmButtonPos = sf::Vector2f(1024.5, 594);
};

PurchaseConfirmState::PurchaseConfirmState(StateStack& stack, Context context)
: State(stack, context)
, mBackground()
, mGUIContainer()
{
    mBackground.setTexture(context.textures->get(Textures::PurchaseConfirmBG));
    mBackground.setPosition(figmaPosition::BackGroundPos);

    auto cancleButton = std::make_shared<GUI::Button>(context, Textures::PurchaseConfirmCancle);
    cancleButton->centerOrigin();
    cancleButton->setPosition(figmaPosition::CancleButtonPos);
    cancleButton->setCallback([this](){
        requestStackPop();
    });

    auto confirmButton = std::make_shared<GUI::Button>(context, Textures::PurchaseConfirmButton);
    confirmButton->centerOrigin();
    confirmButton->setPosition(figmaPosition::ConfirmButtonPos);
    confirmButton->setCallback([this](){
        requestStackPop();
        requestStackPush(States::PurchaseResult);
    });

    mGUIContainer.pack(cancleButton);
    mGUIContainer.pack(confirmButton);
}

void PurchaseConfirmState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mGUIContainer);
}

bool PurchaseConfirmState::update(sf::Time dt){
    mElapsedTime += dt;
    return false;
}

bool PurchaseConfirmState::handleEvent(const sf::Event& event){

    if(mElapsedTime < sf::seconds(0.4))
        return false;
    sf::RenderWindow &mWindow = *getContext().window;
	mGUIContainer.handleRealTimeInput(mWindow);
    mGUIContainer.handleEvent(event);
    return false;
}

bool PurchaseConfirmState::purchasing(){
    int& curMoney = *getContext().money;
    return true;
}