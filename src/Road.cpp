#include "../include/Road.h"

namespace {
    const std::vector<AnimalData> TableAnimal = initializeAnimalData();
}
namespace {
    const std::vector<VehicleData> TableVehicle = initializeVehicleData();
}
// 50: width each lane

void Road::loadTexture(){
    textureHolder.load(Textures::Road, "../../Media/Textures/Road.png");
	textureHolder.load(Textures::Road1, "../../Media/Textures/Road1.png");

    textureHolder.load(Textures::Elephant, "../../Media/Textures/Elephant.png");
    textureHolder.load(Textures::Rhinoceros, "../../Media/Textures/Rhinoceros.png");
    textureHolder.load(Textures::Small_Dragon, "../../Media/Textures/Small_Dragon.png");
    textureHolder.load(Textures::Red_Dragon, "../../Media/Textures/Red_Dragon.png");
    textureHolder.load(Textures::Green_Dragon, "../../Media/Textures/Green_Dragon.png");
    textureHolder.load(Textures::Blue_Twin_Head_Dragon, "../../Media/Textures/Blue_Twin_Head_Dragon.png");
    textureHolder.load(Textures::Traffic, "../../Media/Textures/Traffic.png");
    textureHolder.load(Textures::Truck, "../../Media/Textures/Truck.png");
    textureHolder.load(Textures::Car, "../../Media/Textures/Car.png");
}

Road::Road(sf::Vector2f spawnPos, bool checkLine)
: Lane()
,animals()
,hasTraffic(rand()%2)
, startPos(spawnPos) {
    loadTexture();
    if (checkLine == 0) sprite.setTexture(textureHolder.get(Textures::Road));
    else sprite.setTexture(textureHolder.get(Textures::Road1));
    sf::IntRect textureRect(0, 0, 3000, 152);
    //sprite.scale(0.5f,0.6f);
    sprite.setTextureRect(textureRect);
    if(hasTraffic){
        buildTraffic();
        generateVehicle();
    }
    else {
        generateAnimal();
    }
}

void Road::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}

void Road::updateCurrent(sf::Time dt){
    
    if(hasTraffic){
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
                    vehicles[i]->setVelocity(1.0 * TableAnimal[kind].speed-100, 0);
                }
                 else{
                    vehicles[i]->setVelocity(-1.0 * (TableAnimal[kind].speed-100), 0);
                }
            }
            break;
        case 2:
            for(int i=0; i < numOfObject; i++){
                 if(!this->isReverse()){
                    vehicles[i]->setVelocity(1.0 * TableAnimal[kind].speed, 0);
                }
                 else{
                    vehicles[i]->setVelocity(-1.0 * TableAnimal[kind].speed, 0);
                }
            }
            break;
        }
         if(!this->isReverse() && vehicles[firstObjectIndex]->getPosition().x >= 0) {
            vehicles[lastObjectIndex]->setPosition(-TableVehicle[vehicles[lastObjectIndex]->getType()].distanceBetweenVehicle, startPos.y + 75);
            firstObjectIndex = lastObjectIndex;
            lastObjectIndex = (lastObjectIndex + numOfObject - 1) % numOfObject;
        }
        if(this->isReverse() && vehicles[lastObjectIndex]->getPosition().x <= 2500) {
            vehicles[firstObjectIndex]->setPosition(TableVehicle[vehicles[firstObjectIndex]->getType()].distanceBetweenVehicle + 2500, startPos.y + 75);
            lastObjectIndex = firstObjectIndex;
            firstObjectIndex = (firstObjectIndex + 1) % numOfObject;
        }
    }else{
        if(!this->isReverse() && animals[firstObjectIndex]->getPosition().x >= 0) {
            animals[lastObjectIndex]->setPosition(-TableAnimal[animals[lastObjectIndex]->getType()].distanceBetweenAnimal, startPos.y);
            firstObjectIndex = lastObjectIndex;
            lastObjectIndex = (lastObjectIndex + numOfObject - 1) % numOfObject;
        }
        if(this->isReverse() && animals[lastObjectIndex]->getPosition().x <= 2500) {
            animals[firstObjectIndex]->setPosition(TableAnimal[animals[firstObjectIndex]->getType()].distanceBetweenAnimal + 2500, startPos.y);
            lastObjectIndex = firstObjectIndex;
            firstObjectIndex = (firstObjectIndex + 1) % numOfObject;
        }
    }
    Entity::updateCurrent(dt);

}

void Road::generateAnimal(){
    int distance = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 6);
    int randomKindAnimal = dist(gen);
    Animal::Type kind;
    switch(randomKindAnimal) {
    case 1:
        kind = Animal::Elephant;
        break;
    case 2:
        kind = Animal::Rhinoceros;
        break;
    case 3:
        kind = Animal::Small_Dragon;
        break;
    case 4:
        kind = Animal::Red_Dragon;
        break;
    case 5:
        kind = Animal::Green_Dragon;
        break;
    case 6:
        kind = Animal::Blue_Twin_Head_Dragon;
        break;
    default:
        break;
    }
    int randSpawnPos = rand() % 200;
    for(int j = 0; j < numOfObject; j++) {
        std::unique_ptr<Animal> animal(new Animal(kind, textureHolder));
        if(!this->isReverse()){
            animal->setVelocity(1.0 * TableAnimal[kind].speed, 0);
            animal->scale(TableAnimal[kind].scaling.x,TableAnimal[kind].scaling.y);
        }
        else{
            animal->setVelocity(-1.0 * TableAnimal[kind].speed, 0);
            animal->scale(-TableAnimal[kind].scaling.x,TableAnimal[kind].scaling.y);
        }
        animal->setPosition(startPos.x + randSpawnPos + distance, startPos.y);
        distance += TableAnimal[kind].distanceBetweenAnimal;
        animals.push_back(animal.get());
        this->attachChild(std::move(animal));
    }

    lastObjectIndex = numOfObject - 1;
    firstObjectIndex = 0;
}

void Road::generateVehicle(){
    int distance = 0;
    int randomKindVehicle = 1 + rand() % 2;
    
    switch(randomKindVehicle) {
    case 1:
        kind = Vehicle::Truck;
        break;
    case 2:
        kind = Vehicle::Car;
        break;
    }
    int randSpawnPos = rand() % 200;
    for(int j = 0; j < numOfObject; j++) {
        std::unique_ptr<Vehicle> vehicle(new Vehicle(kind, textureHolder));
        if(!this->isReverse()){
            vehicle->setVelocity(1.0 * TableVehicle[kind].speed, 0);
            vehicle->scale(TableVehicle[kind].scaling.x,TableVehicle[kind].scaling.y);
        }
        else{
            vehicle->setVelocity(-1.0 * TableVehicle[kind].speed, 0);
            vehicle->scale(-TableVehicle[kind].scaling.x,TableVehicle[kind].scaling.y);
        }
        vehicle->setPosition(startPos.x + randSpawnPos + distance, startPos.y + 75);
        distance += TableVehicle[kind].distanceBetweenVehicle;
        vehicles.push_back(vehicle.get());
        this->attachChild(std::move(vehicle));
    }

    lastObjectIndex = numOfObject - 1;
    firstObjectIndex = 0;
}

void Road::buildTraffic(){
    int status=rand()%3;
    std::unique_ptr<Traffic> traff(new Traffic(textureHolder,status));
    traffic= traff.get();
    if(!this->isReverse()){
        traff->setPosition(startPos.x+600,startPos.y + 75);
    }else{
         traff->setPosition(startPos.x+1900,startPos.y + 75);
    }
    
    this->attachChild(std::move(traff));
}
