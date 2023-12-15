#include "SettingsState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "TextureManipulate.hpp"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

const float buttonHeight = 210;

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
    
    mBackground.setFillColor(sf::Color(0, 0, 0, 255));
    mBackground.setSize(sf::Vector2f(context.window->getSize()));
	// mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
	
	// Build key binding buttons and labels
	addButtonLabel(Player::MoveLeft,  buttonHeight, "Left", context);
	addButtonLabel(Player::MoveRight, buttonHeight * 2, "Right", context);
	addButtonLabel(Player::MoveUp,    buttonHeight * 3, "Up", context);
	addButtonLabel(Player::MoveDown,  buttonHeight * 4, "Down", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->centerOrigin();
    backButton->setPosition(140.f, context.window->getDefaultView().getSize().y - 50.f);
    backButton->setScale(0.5, 0.5);
    backButton->setColor(sf::Color(96, 130, 182, 200));
	backButton->setText("Back");
	backButton->setCallback(([this]()
	{
        requestStackPop();
	}));

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
}

bool SettingsState::update(sf::Time dt)
{
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
	// Player* player = getContext().player;

	// for (std::size_t i = 0; i < Player::ActionCount; ++i)
	// {
    //     // player->getAssignedKey()
	// 	// sf::Keyboard::Key key = player->getAssignedKey(static_cast<Player::Action>(i));
    //     // mBindingLabels[i]->setText(toString(key));
	// }
}



void SettingsState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	mBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	sf::View mView = (*context.window).getDefaultView();
    mBindingButtons[action]->centerOrigin();
    mBindingButtons[action]->setPosition(mView.getCenter().x, y);
    mBindingButtons[action]->setScale(0.5, 0.5);
	mBindingButtons[action]->setToggle(true);
    mBindingButtons[action]->setColor(sf::Color(96, 130, 182, 200));
    
	setTextButton(action, context);

    sf::Vector2f position = mBindingButtons[action]->getPosition();
    sf::Text tmp;
    tmp.setFont(context.fonts->get(Fonts::Main));
    tmp.setString(text);
    setCenterOrigin(tmp);
    tmp.setPosition({position.x + 300.f, position.y});
    tmp.setCharacterSize(25);
	tmp.setFillColor(sf::Color::White);
    textHold.push_back(tmp);

	mGUIContainer.pack(mBindingButtons[action]);
}

void SettingsState::setTextButton(Player::Action action, Context context){
	sf::Keyboard::Key key = context.player->getAssignedKey(action);
	mBindingButtons[action]->setText(toString(key));
}