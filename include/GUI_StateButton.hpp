#pragma once

#include "GUI_Component.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace GUI
{

class StateButton : public Component
{
public:
    typedef std::shared_ptr<StateButton>		Ptr;
    typedef std::function<void()>		Callback;
public:
    StateButton(const FontHolder& fonts, const TextureHolder& textures, Textures::ID id1, Textures::ID id2);

    void setCallback(Callback callback);
    void centerOrigin(); // additional function
    void setColor(sf::Color color);

    virtual bool isSelectable() const;
    virtual bool isContain(const sf::RenderWindow& window) const;
    virtual void select();
    virtual void deselect();

    virtual void activate();
    virtual void deactivate();

    virtual void handleEvent(const sf::Event& event);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    Callback                mCallback;  
    const sf::Texture&      mTexture1;
    const sf::Texture&      mTexture2;
    sf::Sprite              mSprite;
    bool                    currentState;
    // current state = 0 -> texture1
    // current state = 1 -> texture2
};

}