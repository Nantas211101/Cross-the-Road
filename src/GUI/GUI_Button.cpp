#include "GUI_Button.hpp"
#include "TextureManipulate.hpp"

namespace GUI
{

Button::Button(State::Context context, Textures::ID id)
: mCallback()
, mNormalTexture(context.textures->get(id))
, mSelectedTexture(context.textures->get(id))
, mPressedTexture(context.textures->get(id))
, mSprite()
, mText("", context.fonts->get(Fonts::Main), 100) 
, mIsToggle(false)
, mIsToggleRelease(false)
, mIsOnlyOneTexture(true)
, mSounds(*context.sounds)
{
    mSprite.setTexture(mNormalTexture);
	// setCenterOrigin(mSprite);
    sf::FloatRect bounds = mSprite.getGlobalBounds();
	
	mText.setFillColor(sf::Color::Yellow);
	setCenterOrigin(mText);
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 38.f);
}

Button::Button(State::Context context, Textures::ID id1, Textures::ID id2)
: mCallback()
, mNormalTexture(context.textures->get(id1))
, mSelectedTexture(context.textures->get(id1))
, mPressedTexture(context.textures->get(id2))
, mSprite()
, mText("", context.fonts->get(Fonts::Main), 100)
, mIsToggle(false)
, mIsToggleRelease(false)
, mIsOnlyOneTexture(false)
, mSounds(*context.sounds)
{
	mSprite.setTexture(mNormalTexture);
	sf::FloatRect bounds = mSprite.getGlobalBounds();
}

Button::Button(State::Context context)
: mCallback()
, mNormalTexture(context.textures->get(Textures::ButtonNormal))
, mSelectedTexture(context.textures->get(Textures::ButtonSelected))
, mPressedTexture(context.textures->get(Textures::ButtonPressed))
, mSprite()
, mText("", context.fonts->get(Fonts::Main), 100)
, mIsToggle(false)
, mIsToggleRelease(false)
, mIsOnlyOneTexture(false)
, mSounds(*context.sounds)
{
	mSprite.setTexture(mNormalTexture);
	// setCenterOrigin(mSprite);
	sf::FloatRect bounds = mSprite.getGlobalBounds();

	mText.setFillColor(sf::Color::Yellow);
	setCenterOrigin(mText);
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 38.f);
}
void Button::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Button::setText(const std::string& text, int size)
{
    sf::FloatRect bounds = mSprite.getGlobalBounds();
	mText.setString(text);
	mText.setCharacterSize(size);
	setCenterOrigin(mText);
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 38.f);
}

void Button::setToggle(bool flag)
{
	mIsToggle = flag;
}

void Button::centerOrigin(){
    setOrigin(mSprite.getGlobalBounds().width / 2.f, mSprite.getGlobalBounds().height / 2.f);
}


void Button::setColor(sf::Color color)
{
	mSprite.setColor(color);
}

void Button::setToggleRelease(bool flag)
{
	mIsToggleRelease = flag;
}

bool Button::checkToggle()
{
	// Only do when release the button
	if(mIsToggleRelease)
	{
		if(mCallback)
			mCallback();
		deactivate(); // To set back the texture
		return true;
	}
	return false;
}

bool Button::isSelectable() const
{
    return true;
}

bool Button::isContain(const sf::RenderWindow& window) const
{
    sf::FloatRect bounds = mSprite.getGlobalBounds();
    auto pos = sf::Mouse::getPosition(window);
    return contain(pos, bounds);
}

void Button::select()
{
	Component::select();
	mScale = getScale();
	if(mIsOnlyOneTexture){
		setScale(mScale.x * 1.1 , mScale.y * 1.1);
		mScale = getScale();
	}
	mSprite.setTexture(mSelectedTexture);
	mText.setFillColor(sf::Color::Red);
}

void Button::deselect()
{
	Component::deselect();
	if(mIsOnlyOneTexture){
		setScale(mScale.x / 1.1 , mScale.y / 1.1);
		mScale = getScale();
	}
	mSprite.setTexture(mNormalTexture);
	mText.setFillColor(sf::Color::Yellow);
}

void Button::activate()
{
	Component::activate();

    // If we are toggle then we should show that the button is pressed and thus "toggled".
	if (mIsToggle)
		mSprite.setTexture(mPressedTexture);

	if (mCallback)
		mCallback();

    // If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!mIsToggle)
		deactivate();
	mSounds.play(SoundEffect::Button);
}

void Button::deactivate()
{
	Component::deactivate();

	if (mIsToggle)
	{
        // Reset texture to right one depending on if we are selected or not.
		if (isSelected())
			mSprite.setTexture(mSelectedTexture);
		else
			mSprite.setTexture(mNormalTexture);
		// hel
		// if (mIsToggleRelease && mCallback)
		// 	mCallback();
	}
}

void Button::handleEvent(const sf::Event&)
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

sf::Vector2f Button::getSize() const{
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	sf::Vector2f mScale = getScale();
	return sf::Vector2f(bounds.width * mScale.x, bounds.height * mScale.y);
}

}