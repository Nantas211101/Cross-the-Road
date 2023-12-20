#include "SettingsState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "TextureManipulate.hpp"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

const float buttonHeight = 150;
const float leftRightScale = 0.1;
const sf::Vector2f volumeRectSize = {25.f, 40.f};
// const sf::Color volumeRectColor = sf::Color(0, 0, 0, 100);

namespace initPosition{
	const float ButtonSettingX = 2 * 140.f;
	const float VolumeSettingX = 200.f;
}

namespace volumeRectColor{
	const sf::Color normal = sf::Color(221,219,203);
	const sf::Color active = sf::Color::Cyan;
}

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
, mText("Settings", context.fonts->get(Fonts::Main), 75)
, mVolumeText("Music Theme", context.fonts->get(Fonts::Main), 25)
, mSoundText("Total Volume", context.fonts->get(Fonts::Main), 25)
, mSounds(*context.sounds)
, mMusic(*context.music)
, currentVolume(mMusic.getVolume() / 10 - 1)
, currentSound(mSounds.getVolume() / 10 - 1)
{
    
    mBackground.setFillColor(sf::Color(0, 0, 0, 255));
    mBackground.setSize(sf::Vector2f(context.window->getSize()));
	// mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
	
	sf::Vector2f pos = context.window->getView().getSize();
	// Build key binding buttons and labels
	addButtonLabel(Player::MoveLeft,  buttonHeight + pos.y / 10.f, "Left", context);
	addButtonLabel(Player::MoveRight, buttonHeight * 2 + pos.y / 10.f, "Right", context);
	addButtonLabel(Player::MoveUp,    buttonHeight * 3 + pos.y / 10.f, "Up", context);
	addButtonLabel(Player::MoveDown,  buttonHeight * 4 + pos.y / 10.f, "Down", context);
	mText.setFillColor(sf::Color::White);
	mText.setPosition(pos.x / 2.f, pos.y / 10.f);
	centerOrigin(mText);
	mText.setOutlineThickness(5.f);
	mText.setOutlineColor(sf::Color::Blue);
	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->centerOrigin();
    backButton->setPosition(140.f, /*context.window->getDefaultView().getSize().y -*/ 50.f);
    backButton->setScale(0.5, 0.5);
    backButton->setColor(sf::Color(96, 130, 182, 200));
	backButton->setText("Back");
	backButton->setCallback(([this]()
	{
        requestStackPop();
	}));

	setVolumeSetting(context);
	setSoundSetting(context);

	mGUIContainer.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	// window.draw(mBackgroundSprite);
    window.draw(mBackground);
	window.draw(mGUIContainer);
    for(sf::Text tmp : textHold)
        window.draw(tmp);
	for(sf::RectangleShape tmp : volumeRectangleHold)
		window.draw(tmp);
	for(sf::RectangleShape tmp : soundRectangleHold)
		window.draw(tmp);
	window.draw(mText);
	window.draw(mVolumeText);
	window.draw(mSoundText);
}

bool SettingsState::update(sf::Time dt)
{
	updateVolumeSetting(currentVolume, volumeRectangleHold, volumeLeftButtonPos, volumeRightButtonPos, mMusic);
	updateVolumeSetting(currentSound, soundRectangleHold, soundLeftButtonPos, soundRightButtonPos, mSounds);
	
	return false;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	
	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
				mBindingButtons[action]->deactivate();
                mBindingButtons[action]->setText(toString(event.key.code));
				setTextButton(Player::MoveLeft, getContext());
				setTextButton(Player::MoveRight, getContext());
				setTextButton(Player::MoveDown, getContext());
				setTextButton(Player::MoveUp, getContext());
			}
			break;
		}
	}
	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		updateLabels();
	else
    {
        sf::RenderWindow &mWindow = *getContext().window;
        mGUIContainer.handleRealTimeInput(mWindow);
		mGUIContainer.handleEvent(event);
    }

	return false;
}

void SettingsState::updateLabels()
{

}



void SettingsState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	mBindingButtons[action] = std::make_shared<GUI::Button>(context);
	sf::View mView = (*context.window).getDefaultView();
    mBindingButtons[action]->centerOrigin();
    mBindingButtons[action]->setPosition(initPosition::ButtonSettingX, y);
    mBindingButtons[action]->setScale(0.5, 0.5);
	mBindingButtons[action]->setToggle(true);
    mBindingButtons[action]->setColor(sf::Color(96, 130, 182, 200));
    
	setTextButton(action, context);

    sf::Vector2f position = mBindingButtons[action]->getPosition();
    sf::Text tmp;
    tmp.setFont(context.fonts->get(Fonts::Main));
    tmp.setString(text);
    setCenterOrigin(tmp);
    tmp.setPosition({initPosition::ButtonSettingX * 2, position.y});
    tmp.setCharacterSize(25);
	tmp.setFillColor(sf::Color::White);
    textHold.push_back(tmp);

	mGUIContainer.pack(mBindingButtons[action]);
}

void SettingsState::setTextButton(Player::Action action, Context context){
	sf::Keyboard::Key key = context.player->getAssignedKey(action);
	mBindingButtons[action]->setText(toString(key));
}

void SettingsState::setVolumeSetting(State::Context context){
	sf::Vector2f pos = getContext().window->getView().getSize();
	
	auto rightButton = std::make_shared<GUI::Button>(context, Textures::RightButton);
	rightButton->centerOrigin();
	rightButton->setScale(leftRightScale, leftRightScale);
	rightButton->setPosition(pos.x - 300.f, buttonHeight * 2 + pos.y / 10.f);
	rightButton->setCallback([this] (){
		++currentVolume;
	});
	
	volumeRightButtonPos = rightButton->getPosition();

	auto leftButton = std::make_shared<GUI::Button>(context, Textures::LeftButton);
	leftButton->centerOrigin();
	leftButton->setScale(leftRightScale, leftRightScale);
	leftButton->setPosition(pos.x - 800.f, buttonHeight * 2 + pos.y / 10.f);
	leftButton->setCallback([this] (){
		--currentVolume;
	});

	volumeLeftButtonPos = leftButton->getPosition();
	
	setVolumeRect(sf::Vector2f(leftButton->getPosition().x + 70.f, leftButton->getPosition().y), volumeRectangleHold);
	int add_x = 40.f;
	for(int i = 1; i < 10; ++i){
		setVolumeRect(sf::Vector2f(leftButton->getPosition().x + 70.f + add_x * i, leftButton->getPosition().y), volumeRectangleHold);
	}

	mVolumeText.setFillColor(sf::Color::White);
	mVolumeText.setPosition(pos.x - 150.f, rightButton->getPosition().y);
	centerOrigin(mVolumeText);

	mGUIContainer.pack(rightButton);
	mGUIContainer.pack(leftButton);
}

void SettingsState::setSoundSetting(State::Context context){
	sf::Vector2f pos = getContext().window->getView().getSize();
	
	auto rightButton = std::make_shared<GUI::Button>(context, Textures::RightButton);
	rightButton->centerOrigin();
	rightButton->setScale(leftRightScale, leftRightScale);
	rightButton->setPosition(pos.x - 300.f, buttonHeight + pos.y / 10.f);
	rightButton->setCallback([this] (){
		++currentSound;
	});
	
	soundRightButtonPos = rightButton->getPosition();

	auto leftButton = std::make_shared<GUI::Button>(context, Textures::LeftButton);
	leftButton->centerOrigin();
	leftButton->setScale(leftRightScale, leftRightScale);
	leftButton->setPosition(pos.x - 800.f, buttonHeight + pos.y / 10.f);
	leftButton->setCallback([this] (){
		--currentSound;
	});

	soundLeftButtonPos = leftButton->getPosition();
	
	setVolumeRect(sf::Vector2f(leftButton->getPosition().x + 70.f, leftButton->getPosition().y), soundRectangleHold);
	int add_x = 40.f;
	for(int i = 1; i < 10; ++i){
		setVolumeRect(sf::Vector2f(leftButton->getPosition().x + 70.f + add_x * i, leftButton->getPosition().y), soundRectangleHold);
	}

	mSoundText.setFillColor(sf::Color::White);
	mSoundText.setPosition(pos.x - 150.f, rightButton->getPosition().y);
	centerOrigin(mSoundText);

	mGUIContainer.pack(rightButton);
	mGUIContainer.pack(leftButton);
}

void SettingsState::setVolumeRect(sf::Vector2f pos, std::vector<sf::RectangleShape>& rectangleHold){
	rectangleHold.push_back(sf::RectangleShape(volumeRectSize));
	sf::RectangleShape& rectangle = rectangleHold.back();
	rectangle.setFillColor(volumeRectColor::normal);
	centerOrigin(rectangle);
	rectangle.setPosition(pos);
}

template <typename T>
void SettingsState::updateVolumeSetting(int& currentAudio, std::vector<sf::RectangleShape>& rectangleHold, sf::Vector2f leftButtonPos, sf::Vector2f rightButtonPos, T& audio){
	if(currentAudio < -1)
		currentAudio = -1;
	else if(currentAudio > 9)
		currentAudio = 9;
	sf::Vector2f pos = getContext().window->getView().getSize();
	sf::Vector2f mousePos = getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window));

	if(mousePos.x >= leftButtonPos.x && mousePos.x <= rightButtonPos.x){
		for(int i = 0; i < rectangleHold.size(); ++i){
			sf::RectangleShape rectangle = rectangleHold[i];
			sf::FloatRect bounds = rectangle.getGlobalBounds();
			if(bounds.contains(mousePos)){
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					currentAudio = i;
				}
			}
		}
	}

	for(int i = 0; i < rectangleHold.size(); ++i){
		sf::RectangleShape& rectangle = rectangleHold[i];
		sf::FloatRect bounds = rectangle.getLocalBounds();
		if(i <= currentAudio)
			rectangle.setFillColor(volumeRectColor::active);
		else
			rectangle.setFillColor(volumeRectColor::normal);
	}

	audio.setVolume((currentAudio + 1) * 10.f);

}