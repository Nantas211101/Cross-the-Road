#pragma once

#include <GUI_Component.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <State.hpp>

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
    Button(State::Context context, Textures::ID id);
    Button(State::Context context, Textures::ID id1, Textures::ID id2);
    Button(State::Context context);
    void setCallback(Callback callback);
    void setText(const std::string& text, int size = 100);
    void setToggle(bool flag);
    void centerOrigin(); // additional function
    void setColor(sf::Color color);
    void setToggleRelease(bool flag);
    void setFlagSelection(bool flag);
    sf::Vector2f getSize() const;
    
    virtual bool checkToggle();
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
    bool                    mIsToggleRelease;
    bool                    mIsOnlyOneTexture;
    sf::Vector2f            mScale;
    SoundPlayer&            mSounds;
};

}