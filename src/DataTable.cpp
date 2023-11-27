#include "../include/DataTable.h"
#include "../include/Animal.h"
#include "../include/Log.h"
#include "../include/TextureHolder.h"
#include "../include/Vehicle.h"

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
    data[Animal::Elephant].speed = 120.f;
    data[Animal::Elephant].distanceBetweenAnimal = 600;
    data[Animal::Elephant].texture = Textures::Elephant;
    data[Animal::Elephant].scaling = sf::Vector2f(1.6, 1.6);
    data[Animal::Elephant].numOfFrames = 3;
    data[Animal::Elephant].pictureWidth = 288;
    data[Animal::Elephant].pictureHeight = 79;

    data[Animal::Small_Dragon].speed = 260.f;
    data[Animal::Small_Dragon].distanceBetweenAnimal = 500;
    data[Animal::Small_Dragon].texture = Textures::Small_Dragon;
    data[Animal::Small_Dragon].scaling = sf::Vector2f(1.7, 1.7);
    data[Animal::Small_Dragon].numOfFrames = 3;
    data[Animal::Small_Dragon].pictureWidth = 192;
    data[Animal::Small_Dragon].pictureHeight = 66;

    data[Animal::Green_Dragon].speed = 180.f;
    data[Animal::Green_Dragon].distanceBetweenAnimal = 800;
    data[Animal::Green_Dragon].texture = Textures::Green_Dragon;
    data[Animal::Green_Dragon].scaling = sf::Vector2f(1.7, 1.7);
    data[Animal::Green_Dragon].numOfFrames = 3;
    data[Animal::Green_Dragon].pictureWidth = 365;
    data[Animal::Green_Dragon].pictureHeight = 96;

    data[Animal::Red_Dragon].speed = 200.f;
    data[Animal::Red_Dragon].distanceBetweenAnimal = 800;
    data[Animal::Red_Dragon].texture = Textures::Red_Dragon;
    data[Animal::Red_Dragon].scaling = sf::Vector2f(1.4, 1.3);
    data[Animal::Red_Dragon].numOfFrames = 3;
    data[Animal::Red_Dragon].pictureWidth = 432;
    data[Animal::Red_Dragon].pictureHeight = 96;

    data[Animal::Blue_Twin_Head_Dragon].speed = 150.f;
    data[Animal::Blue_Twin_Head_Dragon].distanceBetweenAnimal = 500;
    data[Animal::Blue_Twin_Head_Dragon].texture = Textures::Blue_Twin_Head_Dragon;
    data[Animal::Blue_Twin_Head_Dragon].scaling = sf::Vector2f(1.4, 1.4);
    data[Animal::Blue_Twin_Head_Dragon].numOfFrames = 3;
    data[Animal::Blue_Twin_Head_Dragon].pictureWidth = 432;
    data[Animal::Blue_Twin_Head_Dragon].pictureHeight = 94;

    data[Animal::Rhinoceros].speed = 150.f;
    data[Animal::Rhinoceros].distanceBetweenAnimal = 700;
    data[Animal::Rhinoceros].texture = Textures::Rhinoceros;
    data[Animal::Rhinoceros].scaling = sf::Vector2f(1.2, 1.2);
    data[Animal::Rhinoceros].numOfFrames = 4;
    data[Animal::Rhinoceros].pictureWidth = 615;
    data[Animal::Rhinoceros].pictureHeight = 90;

    return data;
}

std::vector<VehicleData> initializeVehicleData(){
      std::vector<VehicleData> data(Vehicle::TypeCount);
    data[Vehicle::Truck].speed = 200.f;
    data[Vehicle::Truck].distanceBetweenVehicle = 600;
    data[Vehicle::Truck].texture = Textures::Truck;
    data[Vehicle::Truck].scaling = sf::Vector2f(0.4, 0.4);
    

    data[Vehicle::Car].speed = 400.f;
    data[Vehicle::Car].distanceBetweenVehicle = 800;
    data[Vehicle::Car].texture = Textures::Car;
    data[Vehicle::Car].scaling = sf::Vector2f(0.4, 0.4);

    return data;
}