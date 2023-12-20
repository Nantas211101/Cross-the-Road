#pragma once

#include <ResourceIdentifiers.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

class MusicPlayer : private sf::NonCopyable
{
	public:
									MusicPlayer();

		void						play(Music::ID theme);
		void						stop();

		void						setPaused(bool paused);
		void						setVolume(float volume);
		void 						setImmediateVolume(float volume);
		float 						getVolume() const;

	private:
		sf::Music							mMusic;
        // The sf::Music object have to be alive if we want the music be playe normarly
		std::map<Music::ID, std::string>	mFilenames;
		float								mVolume;
};