#include "../include/DataTable.h"


std::vector<LogData> initializeLogData() {
    std::vector<LogData> data(Log::TypeCount);
    data[Log::Log1].speed = 200.f;
    data[Log::Log1].distanceBetweenLog = 500;
    data[Log::Log1].texture = Textures::Log1;
    data[Log::Log1].scaling = sf::Vector2f(0.5, 0.6);

    data[Log::Log2].speed = 200.f;
    data[Log::Log2].distanceBetweenLog = 850;
    data[Log::Log2].texture = Textures::Log1;
    data[Log::Log2].scaling = sf::Vector2f(0.5, 0.6);

    data[Log::Log3].speed = 200.f;
    data[Log::Log3].distanceBetweenLog = 400;
    data[Log::Log3].texture = Textures::Log1;
    data[Log::Log3].scaling = sf::Vector2f(0.5, 0.6);

    data[Log::Crocodile].speed = 60.f;
    data[Log::Crocodile].texture = Textures::Log;
    return data;
}
std::vector<ObstacleData> initializeObstacleData() {
    std::vector<ObstacleData> data(Obstacle::TypeCount);
    data[Obstacle::Tree1].dmg = 0;
    data[Obstacle::Tree1].speed = 0.f;
    data[Obstacle::Tree1].texture = Textures::Tree1;
    data[Obstacle::Tree1].scaling = sf::Vector2f(0.6, 0.6);

    data[Obstacle::Tree2].dmg = 0;
    data[Obstacle::Tree2].speed = 0.f;
    data[Obstacle::Tree2].texture = Textures::Tree2;
    data[Obstacle::Tree2].scaling = sf::Vector2f(0.9, 0.9);

    data[Obstacle::Tree3].dmg = 0;
    data[Obstacle::Tree3].speed = 0.f;
    data[Obstacle::Tree3].texture = Textures::Tree3;
    data[Obstacle::Tree3].scaling = sf::Vector2f(0.5, 0.5);

    data[Obstacle::Rock1].dmg = 0;
    data[Obstacle::Rock1].speed = 0.f;
    data[Obstacle::Rock1].texture = Textures::Rock1;
    data[Obstacle::Rock1].scaling = sf::Vector2f(0.35, 0.35);

    data[Obstacle::Rock2].dmg = 0;
    data[Obstacle::Rock2].speed = 0.f;
    data[Obstacle::Rock2].texture = Textures::Rock2;
    data[Obstacle::Rock2].scaling = sf::Vector2f(0.5, 0.5);

    data[Obstacle::Ruin1].dmg = 0;
    data[Obstacle::Ruin1].speed = 0.f;
    data[Obstacle::Ruin1].texture = Textures::Ruin1;
    data[Obstacle::Ruin1].scaling = sf::Vector2f(0.5, 0.5);

    data[Obstacle::Ruin1].dmg = 0;
    data[Obstacle::Ruin2].speed = 0.f;
    data[Obstacle::Ruin2].texture = Textures::Ruin2;
    data[Obstacle::Ruin2].scaling = sf::Vector2f(0.5, 0.5);

    data[Obstacle::Volcano].dmg = 5;
    data[Obstacle::Volcano].speed = 0.f;
    data[Obstacle::Volcano].texture = Textures::Vocalno;
    data[Obstacle::Volcano].scaling = sf::Vector2f(0.35, 0.35);

    return data;
}
std::vector<AnimalData> initializeAnimalData(){
    std::vector<AnimalData> data(Animal::TypeCount);
    data[Animal::Elephant].dmg = 35;
    data[Animal::Elephant].speed = 120.f;
    data[Animal::Elephant].distanceBetweenAnimal = 600;
    data[Animal::Elephant].texture = Textures::Elephant;
    data[Animal::Elephant].scaling = sf::Vector2f(1.25, 1.25);
    data[Animal::Elephant].numOfFrames = 3;
    data[Animal::Elephant].pictureWidth = 288;
    data[Animal::Elephant].pictureHeight = 79;

    data[Animal::Cow].dmg = 20;
    data[Animal::Cow].speed = 120.f;
    data[Animal::Cow].distanceBetweenAnimal = 500;
    data[Animal::Cow].texture = Textures::Cow;
    data[Animal::Cow].scaling = sf::Vector2f(0.35, 0.35);
    data[Animal::Cow].numOfFrames = 4;
    data[Animal::Cow].pictureWidth = 1075;
    data[Animal::Cow].pictureHeight = 191;

    data[Animal::Small_Dragon].dmg = 30;
    data[Animal::Small_Dragon].speed = 260.f;
    data[Animal::Small_Dragon].distanceBetweenAnimal = 500;
    data[Animal::Small_Dragon].texture = Textures::Small_Dragon;
    data[Animal::Small_Dragon].scaling = sf::Vector2f(1.7, 1.7);
    data[Animal::Small_Dragon].numOfFrames = 3;
    data[Animal::Small_Dragon].pictureWidth = 192;
    data[Animal::Small_Dragon].pictureHeight = 66;

    data[Animal::Green_Dragon].dmg = 40;
    data[Animal::Green_Dragon].speed = 180.f;
    data[Animal::Green_Dragon].distanceBetweenAnimal = 800;
    data[Animal::Green_Dragon].texture = Textures::Green_Dragon;
    data[Animal::Green_Dragon].scaling = sf::Vector2f(1.7, 1.7);
    data[Animal::Green_Dragon].numOfFrames = 3;
    data[Animal::Green_Dragon].pictureWidth = 365;
    data[Animal::Green_Dragon].pictureHeight = 96;

    data[Animal::Red_Dragon].dmg = 40;
    data[Animal::Red_Dragon].speed = 200.f;
    data[Animal::Red_Dragon].distanceBetweenAnimal = 800;
    data[Animal::Red_Dragon].texture = Textures::Red_Dragon;
    data[Animal::Red_Dragon].scaling = sf::Vector2f(1.4, 1.3);
    data[Animal::Red_Dragon].numOfFrames = 3;
    data[Animal::Red_Dragon].pictureWidth = 432;
    data[Animal::Red_Dragon].pictureHeight = 96;

    data[Animal::Blue_Twin_Head_Dragon].dmg = 50;
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

    data[Animal::Monster1].dmg = 85;
    data[Animal::Monster1].speed = 150.f;
    data[Animal::Monster1].distanceBetweenAnimal = 1000;
    data[Animal::Monster1].texture = Textures::Monster1;
    data[Animal::Monster1].scaling = sf::Vector2f(0.6, 0.6);
    data[Animal::Monster1].numOfFrames = 11;
    data[Animal::Monster1].pictureWidth = 4019;
    data[Animal::Monster1].pictureHeight = 394;    

    return data;
}

std::vector<VehicleData> initializeVehicleData(){
    std::vector<VehicleData> data(Vehicle::TypeCount);
    data[Vehicle::Truck].dmg = 40;
    data[Vehicle::Truck].speed = 400.f;
    data[Vehicle::Truck].distanceBetweenVehicle = 800;
    data[Vehicle::Truck].texture = Textures::Truck;
    data[Vehicle::Truck].scaling = sf::Vector2f(0.8, 0.8);
    
    data[Vehicle::BlueCar].dmg = 30;
    data[Vehicle::BlueCar].speed = 300.f;
    data[Vehicle::BlueCar].distanceBetweenVehicle = 600;
    data[Vehicle::BlueCar].texture = Textures::BlueCar;
    data[Vehicle::BlueCar].scaling = sf::Vector2f(1.2,1.2);

    data[Vehicle::SmallCar].dmg = 25;
    data[Vehicle::SmallCar].speed = 300.f;
    data[Vehicle::SmallCar].distanceBetweenVehicle = 600;
    data[Vehicle::SmallCar].texture = Textures::SmallCar;
    data[Vehicle::SmallCar].scaling = sf::Vector2f(1.15,1.15);

    data[Vehicle::Ambulance].dmg = 40;
    data[Vehicle::Ambulance].speed = 1200.f;
    data[Vehicle::Ambulance].distanceBetweenVehicle = 1500;
    data[Vehicle::Ambulance].texture = Textures::Ambulance;
    data[Vehicle::Ambulance].scaling = sf::Vector2f(1.2,1.2);

    data[Vehicle::PoliceCar].dmg = 40;
    data[Vehicle::PoliceCar].speed = 1200.f;
    data[Vehicle::PoliceCar].distanceBetweenVehicle = 1500;
    data[Vehicle::PoliceCar].texture = Textures::PoliceCar;
    data[Vehicle::PoliceCar].scaling = sf::Vector2f(0.25,0.25);

    data[Vehicle::YellowCar].dmg = 30;
    data[Vehicle::YellowCar].speed = 200.f;
    data[Vehicle::YellowCar].distanceBetweenVehicle = 520;
    data[Vehicle::YellowCar].texture = Textures::YellowCar;
    data[Vehicle::YellowCar].scaling = sf::Vector2f(1.1,1.1);

    data[Vehicle::OldCar].dmg = 0;
    data[Vehicle::OldCar].speed = 0.f;
    data[Vehicle::OldCar].distanceBetweenVehicle = 250;
    data[Vehicle::OldCar].texture = Textures::OldCar;
    data[Vehicle::OldCar].scaling = sf::Vector2f(1.1,1.1);

    data[Vehicle::SuperCar].dmg = 35;
    data[Vehicle::SuperCar].speed = 900.f;
    data[Vehicle::SuperCar].distanceBetweenVehicle = 1000;
    data[Vehicle::SuperCar].texture = Textures::SuperCar;
    data[Vehicle::SuperCar].scaling = sf::Vector2f(1.2,1.2);

    return data;
}

std::vector<TrainData> initializeTrainData(){
    std::vector<TrainData> data(Train::TypeCount);
    data[Train::Train1].speed = 700.f;
    data[Train::Train1].texture = Textures::Train1;
    data[Train::Train1].scaling = sf::Vector2f(0.7, 0.7);
    
    data[Train::Train2].speed = 600.f;
    data[Train::Train2].texture = Textures::Train2;
    data[Train::Train2].scaling = sf::Vector2f(0.8, 0.8);
    
    data[Train::Train3].speed = 700.f;
    data[Train::Train3].texture = Textures::Train3;
    data[Train::Train3].scaling = sf::Vector2f(0.75, 0.75);

    return data;
}

std::vector<CharData> initializeCharData() {
    std::vector<CharData> data(MainChar::TypeCount);
    data[MainChar::Player1].hitpoints = 100;
    data[MainChar::Player1].speed = 300.f;
    data[MainChar::Player1].texture = Textures::Standing1;
    data[MainChar::Player1].upTexture = Textures::Up1;
    data[MainChar::Player1].downTexture = Textures::Down1;
    data[MainChar::Player1].leftTexture = Textures::Left1;
    data[MainChar::Player1].rightTexture = Textures::Right1;
    data[MainChar::Player1].pictureHeight = 56;
    data[MainChar::Player1].pictureWidth = 256;
    data[MainChar::Player1].numOfFrames = 4;
    data[MainChar::Player1].timeEachFrame = 0.4;

    data[MainChar::Chicken].hitpoints = 100;
    data[MainChar::Chicken].speed = 200.f;
    data[MainChar::Chicken].texture = Textures::Chicken;

    data[MainChar::Penguin].hitpoints = 150;
    data[MainChar::Penguin].speed = 200.f;
    data[MainChar::Penguin].texture = Textures::Penguin;

    data[MainChar::Sheep].hitpoints = 300;
    data[MainChar::Sheep].speed = 150.f;
    data[MainChar::Sheep].texture = Textures::Sheep;

    data[MainChar::Mallard].hitpoints = 250;
    data[MainChar::Mallard].speed = 200.f;
    data[MainChar::Mallard].texture = Textures::Mallard;

    return data;
}