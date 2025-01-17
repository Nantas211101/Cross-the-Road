#include "Animal.hpp"
#include "SFML/System/Vector2.hpp"
#include <RoadTheme1.hpp>
#include <random>

RoadTheme1::RoadTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos, bool checkLine, Type typeRoad, int difficulty)
:Road(textureHolder, spawnPos, difficulty),
typeRoad(typeRoad)
{
    switch (this->typeRoad){
        case RoadTheme1::AnimalRoad:
            textureHolder->get(Textures::Soil).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::Soil));
            break;
        case RoadTheme1::VehicleRoad:
            if (checkLine == 0) sprite.setTexture(textureHolder->get(Textures::Road));
            else sprite.setTexture(textureHolder->get(Textures::Road1));
            break;
    }

    sf::IntRect textureRect(0, 0, widthOfLane, distanceBetweenLane);
    //sprite.scale(0.5f,0.6f);
    sprite.setTextureRect(textureRect);

    buildLane();
};

void RoadTheme1::buildLane() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    switch(typeRoad){
        case RoadTheme1::VehicleRoad:
            hasTraffic = dist(gen);
            if(hasTraffic)
                buildTraffic();
            generateVehicle();
            break;
        case RoadTheme1::AnimalRoad:
            generateAnimal();
            break;
    }
    setLaneVelocity();

    firstObjectIndex = 0;
    lastObjectIndex = numOfObject - 1;
}

void RoadTheme1::generateAnimal(){
    int distance = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist;
    if (difficulty>=3) 
        dist = std::uniform_int_distribution<int>(1, 2);
    else 
        dist = std::uniform_int_distribution<int>(2, 2);

    int randomKindAnimal = dist(gen);
    Animal::Type kind; 
    switch(randomKindAnimal) {
    case 1:
        kind = Animal::Elephant;
        break;
    case 2:
        kind = Animal::Cow;
        break;
    default:
        break;
    }
    
    std::uniform_int_distribution<int> dist2(minCoefficientRandPos,maxCoefficientRandPos);
    int randSpawnPos = dist2(gen);

    for(int j = 0; j < numOfObject; j++) {
        std::unique_ptr<Animal> animal(new Animal(kind, *textureHolder));
        if(!this->isReverse()){
            animal->setVelocity(1.0 * TableAnimal[kind].speed, 0);
            animal->scale(TableAnimal[kind].scaling.x,TableAnimal[kind].scaling.y);
        }
        else{
            animal->setVelocity(-1.0 * TableAnimal[kind].speed, 0);
            animal->scale(-TableAnimal[kind].scaling.x,TableAnimal[kind].scaling.y);
        }
        animal->setPosition(randSpawnPos*distanceBetweenStartPos + distance, 0);
        distance += TableAnimal[kind].distanceBetweenAnimal;
        animals.push_back(animal.get());
        this->attachChild(std::move(animal));
    }
}

void RoadTheme1::generateVehicle(){
    int distance = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist;
    switch(difficulty){
        case 1:
            dist = std::uniform_int_distribution<int>(2, 4);
            break;
        case 2:
            dist = std::uniform_int_distribution<int>(1, 6);
            break;
        case 3:
            dist = std::uniform_int_distribution<int>(1, 8);
            break;
        case 4:
            dist = std::uniform_int_distribution<int>(1, 8);
            break;
        case 5:
            dist = std::uniform_int_distribution<int>(4, 8);
            break;
    }

    int randomKindVehicle = dist(gen);
    Vehicle::Type kind; 

    switch(randomKindVehicle) {
    case 1:
        kind = Vehicle::OldCar;
        break;
    case 2:
        kind = Vehicle::SmallCar;
        break;
    case 3:
        kind = Vehicle::BlueCar;
        break;
    case 4:
        kind = Vehicle::Truck;
        break;
    case 5:
        kind = Vehicle::PoliceCar;
        break;
    case 6:
        kind = Vehicle::YellowCar;
        break;
    case 7:
        kind = Vehicle::Ambulance;
        break;
    case 8:
        kind = Vehicle::SuperCar;
        break;
    }

    std::uniform_int_distribution<int> dist1(minCoefficientRandPos, maxCoefficientRandPos);
    int randSpawnPos = dist1(gen);

    for(int j = 0; j < numOfObject; j++) {
        std::unique_ptr<Vehicle> vehicle(new Vehicle(kind, *textureHolder));
        if(!this->isReverse()){
            vehicle->setVelocity(1.0 * TableVehicle[kind].speed, 0);
            vehicle->scale(TableVehicle[kind].scaling.x,TableVehicle[kind].scaling.y);
        }
        else{
            vehicle->setVelocity(-1.0 * TableVehicle[kind].speed, 0);
            vehicle->scale(-TableVehicle[kind].scaling.x,TableVehicle[kind].scaling.y);
        }
        vehicle->setPosition(randSpawnPos*distanceBetweenStartPos + distance, 50);
        distance += TableVehicle[kind].distanceBetweenVehicle;
        vehicles.push_back(vehicle.get());
        this->attachChild(std::move(vehicle));
    }
}

void RoadTheme1::buildTraffic(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 8);
    
    int randomKindVehicle = dist(gen);
    std::unique_ptr<Traffic> traff(new Traffic(*textureHolder));
    traffic= traff.get();
    if(!this->isReverse()){
        traff->setPosition(600, 0);
    }else{
         traff->setPosition(2200, 0);
    }
    
    this->attachChild(std::move(traff));
}

void RoadTheme1::updateCurrent(sf::Time dt){
    if(typeRoad == VehicleRoad){
        if (hasTraffic){
            switch (traffic->getTrafficState())
            {
            case 0:
                for(int i=0; i < numOfObject; i++){
                    vehicles[i]->setVelocity(0, 0);
                }
                break;
            case 1:
                for(int i=0; i < numOfObject; i++){
                    if(!this->isReverse()){
                        vehicles[i]->setVelocity(0.6 * TableVehicle[vehicles[i]->getType()].speed, 0);
                    }
                    else{
                        vehicles[i]->setVelocity(-0.6 * (TableVehicle[vehicles[i]->getType()].speed), 0);
                    }
                }
                break;
            case 2:
                for(int i=0; i < numOfObject; i++){
                    if(!this->isReverse()){
                        vehicles[i]->setVelocity(1.0 * TableVehicle[vehicles[i]->getType()].speed, 0);
                    }
                    else{
                        vehicles[i]->setVelocity(-1.0 * TableVehicle[vehicles[i]->getType()].speed, 0);
                    }
                }
                break;
            }
        }
        if(!this->isReverse() && vehicles[firstObjectIndex]->getPosition().x >= 0) {
            vehicles[lastObjectIndex]->setPosition(vehicles[firstObjectIndex]->getPosition().x-TableVehicle[vehicles[lastObjectIndex]->getType()].distanceBetweenVehicle, 50);
            firstObjectIndex = lastObjectIndex;
            lastObjectIndex = (lastObjectIndex + numOfObject - 1) % numOfObject;
        }
        if(this->isReverse() && vehicles[lastObjectIndex]->getPosition().x <= 2500) {
            vehicles[firstObjectIndex]->setPosition(TableVehicle[vehicles[firstObjectIndex]->getType()].distanceBetweenVehicle + vehicles[lastObjectIndex]->getPosition().x, 50);
            lastObjectIndex = firstObjectIndex;
            firstObjectIndex = (firstObjectIndex + 1) % numOfObject;
        }
    }
    else{
        if(!this->isReverse() && animals[firstObjectIndex]->getPosition().x >= 0) {
            animals[lastObjectIndex]->setPosition(animals[firstObjectIndex]->getPosition().x-TableAnimal[animals[lastObjectIndex]->getType()].distanceBetweenAnimal, 0);
            firstObjectIndex = lastObjectIndex;
            lastObjectIndex = (lastObjectIndex + numOfObject - 1) % numOfObject;
        }
        if(this->isReverse() && animals[lastObjectIndex]->getPosition().x <= 2500) {
            animals[firstObjectIndex]->setPosition(TableAnimal[animals[firstObjectIndex]->getType()].distanceBetweenAnimal + animals[lastObjectIndex]->getPosition().x, 0);
            lastObjectIndex = firstObjectIndex;
            firstObjectIndex = (firstObjectIndex + 1) % numOfObject;
        }
    }
}

void RoadTheme1::setLaneVelocity(){
    
    for (auto& it:animals){
        it->setVelocity(transformVelocity(it->getVelocity()));
    }
    for (auto& it:vehicles){
        it->setVelocity(transformVelocity(it->getVelocity()));
    }
}