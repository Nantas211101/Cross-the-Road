#include <PurchaseResultState.hpp>

#include <GUI_Button.hpp>
#include <ResourceIdentifiers.hpp>
#include <DataTable.hpp>
#include <MainChar.hpp>

namespace figmaPosition{
    const sf::Vector2f BackGroundPos = sf::Vector2f(457, 244);
    const sf::Vector2f OkayButtonPos = sf::Vector2f(1024.5, 594);
};

namespace
{
    const std::vector<CharData> Table = initializeCharData();
}

PurchaseResultState::PurchaseResultState(StateStack& stack, Context context)
: State(stack, context)
, mBackground()
, mGUIContainer()
{
    int& curMoney = *context.money;
    int cost = Table[context.player->getMainCharID()].price;
    if(curMoney >= cost){
        curMoney -= cost;
        purchaseSuccess(context);
    }
    else{
        purchaseFail(context);
    }
    mBackground.setPosition(figmaPosition::BackGroundPos);
    
}

void PurchaseResultState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mGUIContainer);
}

bool PurchaseResultState::update(sf::Time dt){
    mElapsedTime += dt;
    return false;
}

bool PurchaseResultState::handleEvent(const sf::Event& event){

    if(mElapsedTime < sf::seconds(0.4))
        return false;
    sf::RenderWindow &mWindow = *getContext().window;
    mGUIContainer.handleRealTimeInput(mWindow);
    mGUIContainer.handleEvent(event);
    return false;
}

void PurchaseResultState::purchaseSuccess(Context context){
    mBackground.setTexture(context.textures->get(Textures::PurchaseSucessBG));
    int maskID = context.player->getMaskID();
    maskID |= convertToMaskID(context.player->getMainCharID());
    context.player->setMaskID(maskID);

    auto OkayButton = std::make_shared<GUI::Button>(context, Textures::OkayButton);
    OkayButton->centerOrigin();
    OkayButton->setPosition(figmaPosition::OkayButtonPos);
    OkayButton->setCallback([this](){
        requestStackPop(); // pop itself
        requestStackPop(); // pop display char state
        requestStackPop(); // pop Choose char state
        requestStackPush(States::ChooseChar);
    });
    
    mGUIContainer.pack(OkayButton);
}

void PurchaseResultState::purchaseFail(Context context){
    mBackground.setTexture(context.textures->get(Textures::PurchaseFailBG));

    auto OkayButton = std::make_shared<GUI::Button>(context, Textures::OkayButton);
    OkayButton->centerOrigin();
    OkayButton->setPosition(figmaPosition::OkayButtonPos);
    OkayButton->setCallback([this](){
        requestStackPop(); // pop itself
        // requestStackPop(); // pop display char state
        // requestStackPush(States::DisplayCharState);
    });
    
    mGUIContainer.pack(OkayButton);
}