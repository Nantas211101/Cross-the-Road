#pragma once 

#include "State.hpp"
#include "GUI_ContainerSET.hpp"

#include <SFML/Graphics.hpp>

class PurchaseResultState : public State{
public:
    PurchaseResultState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    void purchaseSuccess(Context context);
    void purchaseFail(Context context);

private:
    sf::Sprite mBackground;
    GUI::ContainerSet mGUIContainer;
    sf::Time mElapsedTime;
};