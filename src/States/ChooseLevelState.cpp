#include <ChooseLevelState.hpp>

#include <Utility.hpp>
#include <GUI_Button.hpp>

const Textures::ID BackGroundTextureID[3] = {
    Textures::Theme1Screen,
    Textures::Theme2Screen,
    Textures::Theme3Screen,
};

const Textures::ID BackButtonTextureID[3] = {
    Textures::Theme1BackButton,
    Textures::Theme2BackButton,
    Textures::Theme3BackButton,
};

const Textures::ID NormalButtonID[3] = {
    Textures::Theme1NormalButton,
    Textures::Theme2NormalButton,
    Textures::Theme3NormalButton,
};

const Textures::ID SelectedButtonID[3] = {
    Textures::Theme1SelectedButton,
    Textures::Theme2SelectedButton,
    Textures::Theme3SelectedButton,
};

namespace canvaPosition{
    const sf::Vector2f backButtonPos = sf::Vector2f(1524.5, 169.5);
    const sf::Vector2f Button1Pos = sf::Vector2f(494, 500);
    const sf::Vector2f Button2Pos = sf::Vector2f(850, 500);
    const sf::Vector2f Button3Pos = sf::Vector2f(1206, 500);
    const sf::Vector2f Button4Pos = sf::Vector2f(672, 682);
    const sf::Vector2f Button5Pos = sf::Vector2f(1028, 682);
    const sf::Vector2f Level1Pos = Button1Pos;
    const sf::Vector2f Level2Pos = Button2Pos;
    const sf::Vector2f Level3Pos = Button3Pos;
    const sf::Vector2f Level4Pos = Button4Pos;
    const sf::Vector2f Level5Pos = Button5Pos;

}

ChooseLevelState::ChooseLevelState(StateStack& stack, Context context)
: State(stack, context)
, mBackgroundSprite()
, mGUIContainer()
{
    int curThemeID = *context.theme - 1;
    sf::Texture& textures = context.textures->get(BackGroundTextureID[curThemeID]);
    mBackgroundSprite.setTexture(textures);

    auto backButton = std::make_shared<GUI::Button>(context, BackButtonTextureID[curThemeID]);
    backButton->centerOrigin();
    backButton->setPosition(canvaPosition::backButtonPos);
    backButton->setCallback([this](){
        requestStackPop();
        requestStackPush(States::ChooseWorldState);
    });

    setButton(curThemeID, canvaPosition::Button1Pos, Textures::Level1, 1);
    setButton(curThemeID, canvaPosition::Button2Pos, Textures::Level2, 2);
    setButton(curThemeID, canvaPosition::Button3Pos, Textures::Level3, 3);
    setButton(curThemeID, canvaPosition::Button4Pos, Textures::Level4, 4);
    setButton(curThemeID, canvaPosition::Button5Pos, Textures::Level5, 5);

    mGUIContainer.pack(backButton);
}

void ChooseLevelState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
    for(sf::Sprite tmp : mLevelSprite)
        window.draw(tmp);
}

bool ChooseLevelState::update(sf::Time dt)
{
    mElapsedTime += dt;
    mGUIContainer.update(dt);
    return true;
}

bool ChooseLevelState::handleEvent(const sf::Event& event)
{
    if(mElapsedTime < sf::seconds(1.0))
        return false;
    sf::RenderWindow& window = *getContext().window;
    mGUIContainer.handleRealTimeInput(window);
    mGUIContainer.handleEvent(event);
    return false;
}

void ChooseLevelState::handleRealTimeInput()
{

}

void ChooseLevelState::setButton(int curThemeId, sf::Vector2f position, Textures::ID idLv, int lv)
{
    auto Button = std::make_shared<GUI::Button>(getContext(), NormalButtonID[curThemeId], SelectedButtonID[curThemeId]);
    Button->centerOrigin();
    Button->setPosition(position);
    if((*getContext().limitLevel - curThemeId * 5) < lv)
        Button->setColor(sf::Color(0, 0, 0, 50));
    Button->setCallback([this, curThemeId, lv](){
        int& curLevel = *getContext().currentLevel;
        int& limitLevel = *getContext().limitLevel;

        if(limitLevel - curThemeId * 5 < lv)
            return;
        
        curLevel = lv + curThemeId * 5;

        requestStackPop();
        requestStackPush(States::ChooseChar);
    });

    mLevelSprite.push_back(sf::Sprite(getContext().textures->get(idLv)));
    sf::Sprite& Level = mLevelSprite.back();
    centerOrigin(Level);
    Level.setPosition(position);

    mGUIContainer.pack(Button);
}