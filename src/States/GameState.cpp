#include "GameState.hpp"

#include <iostream>

namespace canvaPosition{
	// from center
	const sf::Vector2f PausePosAdding = sf::Vector2f(804.5, -428.5);
}

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(context)
, mPlayer(*context.player)
, mGUIContainer()
, mPauseButton(nullptr)
, mBackground()
{
	auto pauseButton = std::make_shared<GUI::Button>(context, Textures::NormalPauseButton, Textures::NormalPauseButton, Textures::PressedPauseButton);
	pauseButton->setPosition(context.window->getView().getCenter() + canvaPosition::PausePosAdding);
	pauseButton->centerOrigin();
	pauseButton->setToggle(true);
	pauseButton->setCallback([this](){
		requestStackPush(States::Pause);
	});
	mPauseButton = pauseButton;

	mBackground.setFillColor(sf::Color(0, 0, 0, 100));
	mBackground.setSize(sf::Vector2f(30, 30));	
	mBackground.setPosition(context.window->getView().getCenter() + canvaPosition::PausePosAdding);

	mGUIContainer.pack(pauseButton);
	context.music->play(Music::ChooseCharTheme);
}

void GameState::draw()
{
	mWorld.draw();
	mPauseButton->setPosition(getContext().window->getView().getCenter() + canvaPosition::PausePosAdding);
	sf::RenderWindow& window = *getContext().window;
	window.draw(mGUIContainer);
}

bool GameState::update(sf::Time dt)
{
	mElapsedTime += dt;
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	mPauseButton->setPosition(getContext().window->getView().getCenter() + canvaPosition::PausePosAdding);
	mGUIContainer.update(dt);
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	if(mElapsedTime < sf::seconds(1.0))
		return false;
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
		requestStackPush(States::GameOver);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
		requestStackPush(States::Victory);

	mPauseButton->setPosition(getContext().window->getView().getCenter() + canvaPosition::PausePosAdding);
	sf::RenderWindow& window = *getContext().window;
	mGUIContainer.handleRealTimeInput(window);
	mGUIContainer.handleEvent(event);
	return true;
}