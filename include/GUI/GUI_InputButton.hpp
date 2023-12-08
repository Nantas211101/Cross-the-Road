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

class InputButton : public Component
{
public:
    typedef std::shared_ptr<InputButton>	        Ptr;
    typedef std::function<void(std::string st)>    Callback;


public:
    InputButton(const FontHolder& fonts, const TextureHolder& textures);
    InputButton(const FontHolder& fonts, const TextureHolder& textures, Textures::ID id, const std::string& text);
    InputButton(const FontHolder& fonts, const TextureHolder& textures, const std::string& text);
    

    void setCallback(Callback callback);
    void setText(const std::string& text);
    void setToggle(bool flag);
    void centerOrigin(); // additional function
    void setColor(sf::Color color);
    void setFlagHidden(bool flag);

    virtual bool isSelectable() const;
    virtual bool isContain(const sf::RenderWindow& window) const;
    virtual void select();
    virtual void deselect();

    virtual void activate();
    virtual void deactivate();

    virtual void handleEvent(const sf::Event& event);
    virtual void update(sf::Time dt); // additional for InputButton
    

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void fillHiddenText(const std::string &currentText);

private:
    Callback				mCallback;
    const sf::Texture&		mNormalTexture;
    const sf::Texture&		mSelectedTexture;
    const sf::Texture&		mPressedTexture;
    sf::Sprite				mSprite;
    sf::Text				mText;
    sf::Text                mTextHidden;
    bool                    mIsBlink;
    bool					mIsToggle;
    bool                    hiddenFlag;
    bool                    isFirstClick;
    sf::Time                mTime;
    sf::Vector2f            mPos;     
};

}