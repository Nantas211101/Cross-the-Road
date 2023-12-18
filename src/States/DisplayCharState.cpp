#include "DisplayCharState.hpp"

#include "ResourceIdentifiers.hpp"
#include "TextureManipulate.hpp"
#include "Utility.hpp"
#include "GUI_Button.hpp"
#include "SpriteNode.hpp"
#include "DataTable.hpp"

const float speedx = 500.f;
const float scaleCharacte = 5.f;
sf::Vector2f speedMove = {0, 0};
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
, hpRect({3 * mWorldView.getSize().x / 4.f - mWorldView.getSize().x / 6.f, mWorldView.getSize().y / 10.f * 3}, {mWorldView.getSize().x / 3.f, mWorldView.getSize().y / 10.f})
, speedRect({3 * mWorldView.getSize().x / 4.f - mWorldView.getSize().x / 6.f, mWorldView.getSize().y / 10.f * 5}, {mWorldView.getSize().x / 3.f, mWorldView.getSize().y / 10.f})
, mBackground()
// , hpTextureRect({30, 30}, {hpRect.left, hpRect.top + 30})
// , speedTextureRect({30, 41}, {speedRect.left, speedRect.top + 41})
, HP(context.textures->get(Textures::Heart))
, Speed(context.textures->get(Textures::Thunder))
, HPText("HP", context.fonts->get(Fonts::Main), 50)
, SpeedText("Speed", context.fonts->get(Fonts::Main), 50)
, AbilityText("Ability: ???", context.fonts->get(Fonts::Main), 50)
{   
    sf::Vector2f pos = context.window->getView().getSize();
    mBackground.setFillColor(sf::Color(255, 255, 255, 255));
    mBackground.setSize(sf::Vector2f(context.window->getSize()));
    
    mText.setFillColor(sf::Color::Black);
    centerOrigin(mText);
    mText.setPosition(pos.x / 2.f, pos.y / 10.f);

    HP.setScale(0.2, 0.2);
    HP.setPosition(hpRect.left, hpRect.top - 30.f);
    Speed.setScale(0.2, 0.2);
    Speed.setPosition(speedRect.left, speedRect.top - 41.f);

    float hpPercentage = (float) Table[context.player->getMainCharID()].hitpoints / CharData::MaxHitpoints;
    
    HPText.setString(toString(Table[context.player->getMainCharID()].hitpoints));
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

    float speedPercentage = (float) Table[context.player->getMainCharID()].speed / CharData::MaxSpeed;

    SpeedText.setString(toString(Table[context.player->getMainCharID()].speed));
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

    AbilityText.setFillColor(sf::Color::Black);
    centerOrigin(AbilityText);
    AbilityText.setPosition(speedRect.left + speedRect.width / 2.f, pos.y / 10.f * 7);
    
    buildScene();
}

bool DisplayCharState::update(sf::Time dt){
    sf::Vector2f position = mPlayer->getPosition();
    sf::Vector2f destination = mWorldView.getSize() / 4.f;
    if(position.x <= destination.x){
        speedMove = {0, 0};
        mPlayer->setVelocity(0, 0);
    }
    mPlayer->setAnimationDown();
    mPlayer->setVelocity(speedMove);
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
    mWindow.draw(AbilityText);
    mWindow.draw(mSceneGraph);
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
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }
    createMainChar();
}

void DisplayCharState::createMainChar(){
    std::unique_ptr<MainChar> leader(new MainChar(getContext().player->getMainCharID(), *getContext().textures, mWorldView.getSize() / 2.f));
    mPlayer = leader.get();
    mPlayer->setVelocity(-speedx, 0);
    speedMove = mPlayer->getVelocity();
    mPlayer->setAnimationDown();
    mPlayer->setCenterOriginMainChar();
    mPlayer->setScale(scaleCharacte, scaleCharacte);
    mSceneLayers[Moving]->attachChild(std::move(leader));
}
