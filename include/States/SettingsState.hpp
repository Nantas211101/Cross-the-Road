#pragma once

#include "State.hpp"
#include "Player.hpp"
#include "GUI_ContainerSET.hpp"
#include "GUI_Button.hpp"
#include "GUI_Label.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State
{
	public:
										SettingsState(StateStack& stack, Context context);

		virtual void					draw();
		virtual bool					update(sf::Time dt);
		virtual bool					handleEvent(const sf::Event& event);


	private:
		void							updateLabels();
		void							addButtonLabel(Player::Action action, float y, const std::string& text, Context context);
		void							setTextButton(Player::Action action, Context context);
		void 							setVolumeSetting(State::Context context);
		void 							setSoundSetting(State::Context context);
		void 							setVolumeRect(sf::Vector2f pos, std::vector<sf::RectangleShape>& rectangleHold);
		
		template <typename T>
		void							updateVolumeSetting(int& currentAudio, std::vector<sf::RectangleShape>& rectangleHolder, sf::Vector2f leftButton, sf::Vector2f rightButton, T& audio);

		void 							updateSettingPlayerInfo();

	private:
        sf::RectangleShape                                  mBackground;
		sf::Sprite											mBackgroundSprite;
		GUI::ContainerSet									mGUIContainer;
		std::array<GUI::Button::Ptr, Player::ActionCount>	mBindingButtons;
		std::array<GUI::Label::Ptr, Player::ActionCount> 	mBindingLabels;
        std::vector<sf::Text> textHold;
		std::vector<sf::RectangleShape> volumeRectangleHold;
		std::vector<sf::RectangleShape> soundRectangleHold;
		sf::Text											mText;
		sf::Text											mVolumeText;
		sf::Text 											mSoundText;
		SoundPlayer& 										mSounds;
		MusicPlayer& 										mMusic;
		int 												currentVolume;
		int 												currentSound;		
		
		sf::Vector2f 										volumeLeftButtonPos;
		sf::Vector2f 										volumeRightButtonPos;	

		sf::Vector2f										soundLeftButtonPos;
		sf::Vector2f										soundRightButtonPos;								

		sf::Time mElapsedTime;

};
