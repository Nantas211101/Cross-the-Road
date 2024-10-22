#pragma once 

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/Audio.hpp>
#include <list>

class SoundPlayer : private sf::NonCopyable
{
public:
    SoundPlayer();

    void play(SoundEffect::ID effect);
    void play(SoundEffect::ID effect, sf::Vector2f position);

    void removeStoppedSounds();
    void setListenerPosition(sf::Vector2f position);
    sf::Vector2f getListenerPosition() const;

    void setVolume(float volume);
    float getVolume() const;

private:
    SoundBufferHolder mSoundBuffers;
    std::list<sf::Sound> mSounds;
    
};