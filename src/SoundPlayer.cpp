#include <SoundPlayer.hpp>

SoundPlayer::SoundPlayer()
: mSoundBuffers()
, mSounds()
{
    mSoundBuffers.load(SoundEffect::Button, "Media/Sound/Button.wav");
    // .. will adding more
}

void SoundPlayer::play(SoundEffect::ID effect)
{
    mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
    mSounds.back().play();
}

void SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position)
{

}

void SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([] (const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{

}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
    return sf::Vector2f();
}