#include "../include/DataTable.h"
#include "../include/Animal.h"
#include "../include/Log.h"
#include "TextureHolder.h"

std::vector<LogData> initializeLogData() {
    std::vector<LogData> data(Log::TypeCount);
    data[Log::Log1].speed = 200.f;
    data[Log::Log1].distanceBetweenLog = 600;
    data[Log::Log1].texture = Textures::Log;
    data[Log::Log1].scaling = sf::Vector2f(0.8, 0.4);

    data[Log::Log2].speed = 200.f;
    data[Log::Log2].distanceBetweenLog = 1000;
    data[Log::Log2].texture = Textures::Log;
    data[Log::Log2].scaling = sf::Vector2f(1.2, 0.4);

    data[Log::Log3].speed = 200.f;
    data[Log::Log3].distanceBetweenLog = 500;
    data[Log::Log3].texture = Textures::Log;
    data[Log::Log3].scaling = sf::Vector2f(0.6, 0.4);

    data[Log::Crocodile].speed = 60.f;
    data[Log::Crocodile].texture = Textures::Log;
    return data;
}
std::vector<AnimalData> initializeAnimalData(){
    std::vector<AnimalData> data(Animal::TypeCount);
    data[Animal::Elephant].speed = 200.f;
    data[Animal::Elephant].distanceBetweenAnimal = 600;
    data[Animal::Elephant].texture = Textures::Elephant;
    data[Animal::Elephant].scaling = sf::Vector2f(0.4, 0.4);
    

    data[Animal::Bird].speed = 400.f;
    data[Animal::Bird].distanceBetweenAnimal = 800;
    data[Animal::Bird].texture = Textures::Bird;
    data[Animal::Bird].scaling = sf::Vector2f(0.4, 0.4);


    data[Animal::Rhinoceros].speed = 100.f;
    data[Animal::Rhinoceros].distanceBetweenAnimal = 400;
    data[Animal::Rhinoceros].texture = Textures::Rhinoceros;
    data[Animal::Rhinoceros].scaling = sf::Vector2f(-0.45, 0.45);

    return data;
}

std::vector<LaneData> initializeLaneData() {
    std::vector<LaneData> data(Lane::TypeCount);
    data[Lane::Ground].speed = 0;
    data[Lane::Ground].texture = Textures::Ground;

    data[Lane::Road].speed = 0;
    data[Lane::Road].texture = Textures::Road;

    data[Lane::River].speed = 20.f;
    data[Lane::River].texture = Textures::River;

    data[Lane::Grass].speed = 20.f;
    data[Lane::Grass].texture = Textures::Grass;
    return data;
}