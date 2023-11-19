#include "GUI_InputButton.hpp"
#include "TextureManipulate.hpp"

namespace GUI
{

InputButton::InputButton(const FontHolder& fonts, const TextureHolder& textures)
: mCallback()
, mNormalTexture(textures.get(Textures::InputButton1))
, mSelectedTexture(textures.get(Textures::InputButton1))
, mPressedTexture(textures.get(Textures::InputButton1))
, mSprite()
, mText("", fonts.get(Fonts::Main), 100)
, mIsToggle(false)
{
	mSprite.setTexture(mNormalTexture);
	// setCenterOrigin(mSprite);
	sf::FloatRect bounds = mSprite.getGlobalBounds();

	mText.setFillColor(sf::Color::Yellow);
	setCenterOrigin(mText);
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 38.f);
}

InputButton::InputButton(const FontHolder& fonts, const TextureHolder& textures, Textures::ID id)
: mCallback()
, mNormalTexture(textures.get(id))
, mSelectedTexture(textures.get(id))
, mPressedTexture(textures.get(id))
, mSprite()
, mText("", fonts.get(Fonts::Main), 100) 
, mIsToggle(false)
{
    mSprite.setTexture(mNormalTexture);
	// setCenterOrigin(mSprite);
    sf::FloatRect bounds = mSprite.getGlobalBounds();
	
	mText.setFillColor(sf::Color::Yellow);
	setCenterOrigin(mText);
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 38.f);
}

void InputButton::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void InputButton::setText(const std::string& text)
{
    sf::FloatRect bounds = mSprite.getGlobalBounds();
	mText.setString(text);
	setCenterOrigin(mText);
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 38.f);
}

void InputButton::setToggle(bool flag)
{
	mIsToggle = flag;
}

void InputButton::centerOrigin(){
    setOrigin(mSprite.getGlobalBounds().width / 2.f, mSprite.getGlobalBounds().height / 2.f);
}


void InputButton::setColor(sf::Color color)
{
	mSprite.setColor(color);
}

bool InputButton::isSelectable() const
{
    return true;
}

bool InputButton::isContain(const sf::RenderWindow& window) const
{
    sf::FloatRect bounds = mSprite.getGlobalBounds();
    auto pos = sf::Mouse::getPosition(window);
    return contain(pos, bounds);
}

void InputButton::select()
{
	Component::select();
	mSprite.setTexture(mSelectedTexture);
	// mText.setFillColor(sf::Color::Red);
    mText.setFillColor(sf::Color(255, 186, 0));
}

void InputButton::deselect()
{
	Component::deselect();

	mSprite.setTexture(mNormalTexture);
	mText.setFillColor(sf::Color::Yellow);
}

void InputButton::activate()
{
	Component::activate();
    // std::cerr << "activate Input button\n";
    // If we are toggle then we should show that the InputButton is pressed and thus "toggled".
	if (mIsToggle){
        mText.setString("");
        // mText = "";
    	mSprite.setTexture(mPressedTexture);
        mSprite.setColor(sf::Color::Cyan);
    }
	if (mCallback)
		mCallback(mText.getString());

    // If we are not a toggle then deactivate the InputButton since we are just momentarily activated.
	if (!mIsToggle)
		deactivate();
}

void InputButton::deactivate()
{
	Component::deactivate();
    // std::cerr << "deactivate Input button\n";

	if (mIsToggle)
	{
        // Reset texture to right one depending on if we are selected or not.
        mSprite.setColor(sf::Color::White);
		if (isSelected())
			mSprite.setTexture(mSelectedTexture);
		else
			mSprite.setTexture(mNormalTexture);
	}
}

void InputButton::handleEvent(const sf::Event& event)
{
    std::string currentText = mText.getString();
    if(event.type == sf::Event::TextEntered){
        unsigned short unicode = event.text.unicode;
        if(unicode == 8) {// Backspace
            if(currentText.size() > 0)
                currentText.pop_back();
        }
        else if(unicode >= 32 && unicode <= 126)
            currentText += (char)unicode;
        else if(unicode >= 192 && unicode <= 255)
            currentText += (char)unicode;
    }
    setText(currentText);
    if (mCallback)
		mCallback(mText.getString());
}

void InputButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

}