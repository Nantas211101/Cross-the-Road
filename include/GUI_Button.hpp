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

class Button : public Component
{
public:
    typedef std::shared_ptr<Button>		Ptr;
    typedef std::function<void()>		Callback;


public:
    Button(const FontHolder& fonts, const TextureHolder& textures);
    Button(const FontHolder& fonts, const TextureHolder& textures, Textures::ID id);
    
    void setCallback(Callback callback);
    void setText(const std::string& text);
    void setToggle(bool flag);
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
    Callback				mCallback;
    const sf::Texture&		mNormalTexture;
    const sf::Texture&		mSelectedTexture;
    const sf::Texture&		mPressedTexture;
    sf::Sprite				mSprite;
    sf::Text				mText;
    bool					mIsToggle;
};

}