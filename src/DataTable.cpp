#include "DataTable.hpp"
// #include "Animal.h"
// #include "Log.h"
#include "MainChar.hpp"

// std::vector<LogData> initializeLogData() {
//     std::vector<LogData> data(Log::TypeCount);
//     data[Log::Log1].speed = 200.f;
//     data[Log::Log1].distanceBetweenLog = 600;
//     data[Log::Log1].texture = Textures::Log;
//     data[Log::Log1].scaling = sf::Vector2f(0.8, 0.4);

//     data[Log::Log2].speed = 200.f;
//     data[Log::Log2].distanceBetweenLog = 1000;
//     data[Log::Log2].texture = Textures::Log;
//     data[Log::Log2].scaling = sf::Vector2f(1.2, 0.4);

//     data[Log::Log3].speed = 200.f;
//     data[Log::Log3].distanceBetweenLog = 500;
//     data[Log::Log3].texture = Textures::Log;
//     data[Log::Log3].scaling = sf::Vector2f(0.6, 0.4);

//     data[Log::Crocodile].speed = 60.f;
//     data[Log::Crocodile].texture = Textures::Log;
//     return data;
// }
// std::vector<AnimalData> initializeAnimalData(){
//     std::vector<AnimalData> data(Animal::TypeCount);
//     data[Animal::Elephant].speed = 200.f;
//     data[Animal::Elephant].distanceBetweenAnimal = 600;
//     data[Animal::Elephant].texture = Textures::Elephant;
//     data[Animal::Elephant].scaling = sf::Vector2f(0.4, 0.4);
    

//     data[Animal::Bird].speed = 400.f;
//     data[Animal::Bird].distanceBetweenAnimal = 800;
//     data[Animal::Bird].texture = Textures::Bird;
//     data[Animal::Bird].scaling = sf::Vector2f(0.4, 0.4);


//     data[Animal::Rhinoceros].speed = 100.f;
//     data[Animal::Rhinoceros].distanceBetweenAnimal = 400;
//     data[Animal::Rhinoceros].texture = Textures::Rhinoceros;
//     data[Animal::Rhinoceros].scaling = sf::Vector2f(-0.45, 0.45);

//     return data;
// }

std::vector<CharData> initializeCharData(){
    std::vector<CharData> data(MainChar::TypeCount);
    data[MainChar::Chicken].hitpoints = 100;
    data[MainChar::Chicken].speed = 200.f;
    data[MainChar::Chicken].texture = Textures::chicken;

    data[MainChar::Penguin].hitpoints = 150;
    data[MainChar::Penguin].speed = 200.f;
    data[MainChar::Penguin].texture = Textures::penguin;

    data[MainChar::Sheep].hitpoints = 300;
    data[MainChar::Sheep].speed = 150.f;
    data[MainChar::Sheep].texture = Textures::sheep;

    data[MainChar::Mallard].hitpoints = 250;
    data[MainChar::Mallard].speed = 200.f;
    data[MainChar::Mallard].texture = Textures::mallard;

    return data;
}