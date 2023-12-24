#pragma once

#include <State.hpp>
#include <ResourceIdentifiers.hpp>
#include <TextureManipulate.hpp>
#include <GUI_ContainerSet.hpp>

#include <SFML/Graphics.hpp>

class ChooseLevelState : public State{
public:
    ChooseLevelState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    virtual void handleRealTimeInput();

private:
    void setButton(int curThemeId, sf::Vector2f position, Textures::ID idLv, int lv);

private:
    sf::Sprite mBackgroundSprite;
    GUI::ContainerSet mGUIContainer;
    std::vector<sf::Sprite> mLevelSprite;
};