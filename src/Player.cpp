#include <Player.hpp>

struct MainCharMover
{
	MainCharMover(Player::Action action) : action(action) {}

	void operator() (MainChar& mainChar, sf::Time) const
	{
		sf::Vector2f pos = mainChar.getPosition();
		switch(action) {
		case Player::MoveUp:
			mainChar.goUp();
			break;
		case Player::MoveDown:
			mainChar.goDown();
			break;
		case Player::MoveLeft:
			mainChar.goLeft();
			break;
		case Player::MoveRight:
			mainChar.goRight();
			break;
		case Player::UseAbility:
			mainChar.useAbility();
			break;
		}
	}
	Player::Action action;
};

Player::Player()
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	mKeyBinding[sf::Keyboard::Space] = UseAbility;

	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's aircraft
	for(auto& pair : mActionBinding)
		pair.second.category = Category::Player;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for(auto pair : mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for(auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	const float playerSpeed = 500.f;
	
	mActionBinding[MoveLeft].action	 = derivedAction<MainChar>(MainCharMover(MoveLeft));
	mActionBinding[MoveRight].action = derivedAction<MainChar>(MainCharMover(MoveRight));
	mActionBinding[MoveUp].action    = derivedAction<MainChar>(MainCharMover(MoveUp));
	mActionBinding[MoveDown].action  = derivedAction<MainChar>(MainCharMover(MoveDown));
	mActionBinding[UseAbility].action = derivedAction<MainChar>(MainCharMover(UseAbility));

	// mActionBinding[MoveLeft].action	 = derivedAction<MainChar>(MainCharMover(-playerSpeed, 0.f));
	// mActionBinding[MoveRight].action = derivedAction<MainChar>(MainCharMover(+playerSpeed, 0.f));
	// mActionBinding[MoveUp].action    = derivedAction<MainChar>(MainCharMover(0.f, -playerSpeed));
	// mActionBinding[MoveDown].action  = derivedAction<MainChar>(MainCharMover(0.f, +playerSpeed));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
			return true;

		default:
			return false;
	}
}

void Player::setMainCharID(MainChar::Type id)
{
    charID = id;
}

MainChar::Type Player::getMainCharID()
{
    return charID;
}

void Player::setMaskID(int id)
{
	maskID = id;
}

int Player::getMaskID()
{
	return maskID;
}

void Player::setUID(int id)
{
	UID = id;
}

int Player::getUID()
{
	return UID;
}