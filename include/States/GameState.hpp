#pragma once

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"
#include <GUI_ContainerSet.hpp>
#include <GUI_Button.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
	public:
							GameState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		World				mWorld;
		Player&				mPlayer;
		GUI::ContainerSet	mGUIContainer;
		GUI::Button::Ptr 	mPauseButton;
		sf::RectangleShape 	mBackground;

		sf::Time mElapsedTime;
};
