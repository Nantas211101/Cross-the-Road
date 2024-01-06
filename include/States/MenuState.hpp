#pragma once

#include "State.hpp"
#include "GUI_Container.hpp"
#include "GUI_ContainerSET.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"

#include <SFML/Graphics.hpp>
#include <array>

class MenuState : public State
{

public:
    MenuState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    void buildScene();
    void saveCurrentPlayerInfo();

private: 
    enum Layer
    {
        Background,
        LayerCount
    };

private:
    SceneNode                           mSceneGraph;
    std::array<SceneNode*, LayerCount>  mSceneLayers;
    sf::View                            mWorldView;
    sf::FloatRect                       mWorldBounds;
    GUI::ContainerSet			        mGUIContainer;
    sf::Time                            mElapsedTime;
};
