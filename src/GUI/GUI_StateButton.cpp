#include "GUI_StateButton.hpp"
#include "TextureManipulate.hpp"

namespace GUI
{

StateButton::StateButton(const FontHolder& fonts, const TextureHolder& textures, Textures::ID id1, Textures::ID id2)
: mCallback()
, mTexture1(textures.get(id1))
, mTexture2(textures.get(id2))
, mSprite()
, currentState(false)
{
    mSprite.setTexture(mTexture1);
    
}

void StateButton::setCallback(Callback callback)
{
    mCallback = std::move(callback);
}

void StateButton::centerOrigin()
{
    sf::FloatRect bounds = mSprite.getGlobalBounds();
    setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    // mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void StateButton::setColor(sf::Color color)
{
    mSprite.setColor(color);
}

bool StateButton::isSelectable() const
{
    return true;
}

bool StateButton::isContain(const sf::RenderWindow& window) const
{
    // return getTransform().transformRect(mSprite.getGlobalBounds()).contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    sf::FloatRect bounds = mSprite.getGlobalBounds();
    auto pos = sf::Mouse::getPosition(window);
    return contain(pos, bounds);
}

void StateButton::select()
{
    Component::select();
    setScale(1.2, 1.2);
    // mSprite.setScale(1.1, 1.1);
    // mSprite.setTexture(mTexture2);
}

void StateButton::deselect()
{
    Component::deselect();
    setScale(1, 1);
    // mSprite.setScale(1, 1);
}

void StateButton::activate()
{
    Component::activate();

    if(mCallback)
        mCallback();

    if(currentState)
        mSprite.setTexture(mTexture1);
    else
        mSprite.setTexture(mTexture2);

    currentState = !currentState;
    deactivate();
}

void StateButton::deactivate()
{
    Component::deactivate();
}

void StateButton::handleEvent(const sf::Event& event)
{

}

void StateButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}

}