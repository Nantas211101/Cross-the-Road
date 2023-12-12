#include "DisplayCharState.hpp"

#include "ResourceIdentifiers.hpp"
#include "TextureManipulate.hpp"
#include "Utility.hpp"
#include "GUI_Button.hpp"
#include "SpriteNode.hpp"
#include "DataTable.hpp"

namespace 
{
    const std::vector<CharData> Table = initializeCharData();
}

DisplayCharState::DisplayCharState(StateStack &stack, Context context)
: State(stack, context)
, mText("Info", context.fonts->get(Fonts::Main), 75)
, mWorldView(context.window->getDefaultView())
, mSceneGraph()
, mSceneLayers()
, mPlayer(nullptr)
, hpRect({mWorldView.getSize().x / 2.f - mWorldView.getSize().x / 6.f, mWorldView.getSize().y / 10.f * 2}, {mWorldView.getSize().x / 3.f, mWorldView.getSize().y / 10.f})
, speedRect({mWorldView.getSize().x / 2.f - mWorldView.getSize().x / 6.f, mWorldView.getSize().y / 10.f * (float)4.5}, {mWorldView.getSize().x / 3.f, mWorldView.getSize().y / 10.f})
, mBackground()
// , hpTextureRect({30, 30}, {hpRect.left, hpRect.top + 30})
// , speedTextureRect({30, 41}, {speedRect.left, speedRect.top + 41})
, HP(context.textures->get(Textures::Heart))
, Speed(context.textures->get(Textures::Thunder))
, HPText("HP", context.fonts->get(Fonts::Main), 50)
, SpeedText("Speed", context.fonts->get(Fonts::Main), 50)
{
    sf::Vector2f pos = context.window->getView().getSize();
    mBackground.setFillColor(sf::Color(255, 255, 255, 255));
    mBackground.setSize(sf::Vector2f(context.window->getSize()));
    
    mText.setFillColor(sf::Color::Black);
    centerOrigin(mText);
    mText.setPosition(pos.x / 2.f, pos.y / 10.f);

    createMainChar();  

    HP.setScale(0.2, 0.2);
    HP.setPosition(hpRect.left, hpRect.top - 30.f);
    Speed.setScale(0.2, 0.2);
    Speed.setPosition(speedRect.left, speedRect.top - 41.f);

    float hpPercentage = (float) Table[mPlayer->getMainCharType()].hitpoints / CharData::MaxHitpoints;
    
    HPText.setString(toString(Table[mPlayer->getMainCharType()].hitpoints));
    HPText.setFillColor(sf::Color::White);
    centerOrigin(HPText);
    HPText.setPosition(hpRect.left + hpRect.width / 2.f, hpRect.top + hpRect.height / 2.f);

    hpBarBackground.setFillColor(sf::Color(220, 220, 220, 255));
    hpBarBackground.setOutlineThickness(10.f);
    hpBarBackground.setOutlineColor(sf::Color(96, 130, 182, 200));
    hpBarBackground.setPosition(hpRect.left, hpRect.top);
    hpBarBackground.setSize({hpRect.width, hpRect.height});

    hpBar.setFillColor(sf::Color(119, 221, 119, 255));
    hpBar.setPosition(hpRect.left, hpRect.top);
    hpBar.setSize({hpRect.width * hpPercentage, hpRect.height});

    float speedPercentage = (float) Table[mPlayer->getMainCharType()].speed / CharData::MaxSpeed;

    SpeedText.setString(toString(Table[mPlayer->getMainCharType()].speed));
    SpeedText.setFillColor(sf::Color::White);
    centerOrigin(SpeedText);
    SpeedText.setPosition(speedRect.left + speedRect.width / 2.f, speedRect.top + speedRect.height / 2.f);

    speedBarBackground.setFillColor(sf::Color(220, 220, 220, 255));
    speedBarBackground.setOutlineThickness(10.f);
    speedBarBackground.setOutlineColor(sf::Color(96, 130, 182, 200));
    speedBarBackground.setPosition(speedRect.left, speedRect.top);
    speedBarBackground.setSize({speedRect.width, speedRect.height});

    speedBar.setFillColor(sf::Color(255, 191, 0, 255));
    speedBar.setPosition(speedRect.left, speedRect.top);
    speedBar.setSize({speedRect.width * speedPercentage, speedRect.height});

}

bool DisplayCharState::update(sf::Time dt){
    mSceneGraph.update(dt);
    return false;
}

void DisplayCharState::draw(){
    sf::RenderWindow &mWindow = *getContext().window;
    mWindow.draw(mBackground);
    mWindow.draw(mText);
    mWindow.draw(hpBarBackground);  
    mWindow.draw(hpBar);
    mWindow.draw(speedBarBackground);
    mWindow.draw(speedBar);
    mWindow.draw(HP);
    mWindow.draw(Speed);
    mWindow.draw(HPText);
    mWindow.draw(SpeedText);
}

bool DisplayCharState::handleEvent(const sf::Event &event){
    if(event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Escape)
            requestStackPop();
    }
    return false;
}

void DisplayCharState::handleRealTimeInput(){
    return;
}

void DisplayCharState::buildScene(){

}

void DisplayCharState::createMainChar(){
    std::unique_ptr<MainChar> leader(new MainChar(getContext().player->getMainCharID(), *getContext().textures));
    mPlayer = leader.get();
    mPlayer->setPosition(mWorldView.getSize() / 2.f);
}
