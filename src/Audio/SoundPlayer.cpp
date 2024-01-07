#include <SoundPlayer.hpp>
#include <math.h>

namespace
{
    const float ListenerZ = 300.f;
    const float Attenuation = 8.f;
    const float MinDistance2D = 200.f;
    const float MinDistance3D = 
        std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

SoundPlayer::SoundPlayer()
: mSoundBuffers()
, mSounds()
{
    mSoundBuffers.load(SoundEffect::Button, "Media/Sound/Button.wav");
    // River
    mSoundBuffers.load(SoundEffect::River, "Media/Sound/RiverSound/River.wav");
    mSoundBuffers.load(SoundEffect::LavaRiver, "Media/Sound/RiverSound/LavaRiver.wav");
    
    // Animal
    mSoundBuffers.load(SoundEffect::Elephant, "Media/Sound/AnimalSound/Elephant.wav");
    mSoundBuffers.load(SoundEffect::Cow, "Media/Sound/AnimalSound/Cow.wav");
    mSoundBuffers.load(SoundEffect::Dragon, "Media/Sound/AnimalSound/Dragon.wav");
    mSoundBuffers.load(SoundEffect::Rhino, "Media/Sound/AnimalSound/Rhino.wav");
    mSoundBuffers.load(SoundEffect::Monster, "Media/Sound/AnimalSound/Monster.wav");
    mSoundBuffers.load(SoundEffect::Reindeer, "Media/Sound/AnimalSound/Reindeer.wav");
    mSoundBuffers.load(SoundEffect::Bear, "Media/Sound/AnimalSound/Bear.wav");
    mSoundBuffers.load(SoundEffect::Penguin, "Media/Sound/AnimalSound/Penguin.wav");
    mSoundBuffers.load(SoundEffect::Wolf, "Media/Sound/AnimalSound/Wolf.wav");

    // Vehicle
    mSoundBuffers.load(SoundEffect::Truck, "Media/Sound/VehicleSound/Truck.wav");
    mSoundBuffers.load(SoundEffect::Car, "Media/Sound/VehicleSound/Car.wav");
    mSoundBuffers.load(SoundEffect::Ambulance, "Media/Sound/VehicleSound/Ambulance.wav");
    mSoundBuffers.load(SoundEffect::PoliceCar, "Media/Sound/VehicleSound/PoliceCar.wav");
    mSoundBuffers.load(SoundEffect::OldCar, "Media/Sound/VehicleSound/OldCar.wav");
    mSoundBuffers.load(SoundEffect::IceCreamTruck, "Media/Sound/VehicleSound/IceCreamTruck.wav");
    mSoundBuffers.load(SoundEffect::SantaClaus, "Media/Sound/VehicleSound/SantaClaus.wav");

    // Obstacle
    mSoundBuffers.load(SoundEffect::Rock, "Media/Sound/ObstacleSound/Rock.wav");
    mSoundBuffers.load(SoundEffect::Tree, "Media/Sound/ObstacleSound/Tree.wav");
    mSoundBuffers.load(SoundEffect::Volcano, "Media/Sound/ObstacleSound/Volcano.wav");
    mSoundBuffers.load(SoundEffect::SnowMan, "Media/Sound/ObstacleSound/SnowMan.wav");
    mSoundBuffers.load(SoundEffect::Coin, "Media/Sound/ObstacleSound/Coin.wav");

    // Train
    mSoundBuffers.load(SoundEffect::Train1, "Media/Sound/TrainSound/Train1.wav");
    mSoundBuffers.load(SoundEffect::Train2, "Media/Sound/TrainSound/Train2.wav");

    // Player
    mSoundBuffers.load(SoundEffect::Ability, "Media/Sound/CharacterSound/Ability.wav");
}

void SoundPlayer::play(SoundEffect::ID effect)
{
    play(effect, getListenerPosition());
}

void SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position)
{
    mSounds.push_back(sf::Sound());
    sf::Sound& sound = mSounds.back();

    sound.setBuffer(mSoundBuffers.get(effect));
    sound.setPosition(position.x, -position.y, 0.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);

    sound.play();
}

void SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([] (const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
    // the coordinate x the same
    // the coordinate y in the screen point down, why the coordinate y in sound upward

}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
    sf::Vector3f position = sf::Listener::getPosition();
    return sf::Vector2f(position.x, -position.y);
}

void SoundPlayer::setVolume(float volume)
{
    sf::Listener::setGlobalVolume(volume);
}

float SoundPlayer::getVolume() const
{
    return sf::Listener::getGlobalVolume();
}