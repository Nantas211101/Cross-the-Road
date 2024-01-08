#include <RoadTheme3.hpp>

RoadTheme3::RoadTheme3(TextureHolder* textureHolder, sf::Vector2f spawnPos, bool checkLine, int difficulty)
:Road(textureHolder, spawnPos, difficulty)
{
    textureHolder->get(Textures::LavaRoad).setRepeated(true);
    sprite.setTexture(textureHolder->get(Textures::LavaRoad));
    sf::IntRect textureRect(0, 0, widthOfLane, distanceBetweenLane);
    //sprite.scale(0.5f,0.6f);
    sprite.setTextureRect(textureRect);

    buildLane();
};

void RoadTheme3::buildLane() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1);
    typeRoad = dist(gen);
    generateAnimal();
    firstObjectIndex = 0;
    lastObjectIndex = numOfObject - 1;
}

void RoadTheme3::generateAnimal(){
    int distance = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 4);
    int randomKindAnimal = dist(gen);
    Animal::Type kind; 

    switch(randomKindAnimal) {
    case 0:
        kind = Animal::Small_Dragon;
        break;
    case 1:
        kind = Animal::Green_Dragon;
        break;
    case 2:
        kind = Animal::Red_Dragon;
        break;
    case 3:
        kind = Animal::Blue_Twin_Head_Dragon;
        break;
    case 4:
        kind = Animal::Monster1;
        break;
    }
    std::uniform_int_distribution<int> dist2(minCoefficientRandPos, maxCoefficientRandPos);
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
        animal->setPosition(randSpawnPos*distanceBetweenStartPos + distance, -20);
        distance += TableAnimal[kind].distanceBetweenAnimal;
        animals.push_back(animal.get());
        this->attachChild(std::move(animal));
    }
}

void RoadTheme3::generateVehicle(){
    int distance = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 8);
    int randomKindVehicle = dist(gen);
    Vehicle::Type kind; 

    switch(randomKindVehicle) {
    case 1:
        kind = Vehicle::Truck;
        break;
    case 2:
        kind = Vehicle::SmallCar;
        break;
    case 3:
        kind = Vehicle::BlueCar;
        break;
    case 4:
        kind = Vehicle::Ambulance;
        break;
    case 5:
        kind = Vehicle::PoliceCar;
        break;
    case 6:
        kind = Vehicle::YellowCar;
        break;
    case 7:
        kind = Vehicle::OldCar;
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
        vehicle->setPosition(randSpawnPos*distanceBetweenStartPos + distance, startPos.y + 75);
        distance += TableVehicle[kind].distanceBetweenVehicle;
        vehicles.push_back(vehicle.get());
        this->attachChild(std::move(vehicle));
    }
}

void RoadTheme3::updateCurrent(sf::Time dt){
    switch(typeRoad){
        case 0:
            if(!this->isReverse() && vehicles[firstObjectIndex]->getPosition().x >= 0) {
                vehicles[lastObjectIndex]->setPosition(vehicles[firstObjectIndex]->getPosition().x-TableVehicle[vehicles[lastObjectIndex]->getType()].distanceBetweenVehicle, startPos.y + 75);
                firstObjectIndex = lastObjectIndex;
                lastObjectIndex = (lastObjectIndex + numOfObject - 1) % numOfObject;
            }
            if(this->isReverse() && vehicles[lastObjectIndex]->getPosition().x <= 2500) {
                vehicles[firstObjectIndex]->setPosition(TableVehicle[vehicles[firstObjectIndex]->getType()].distanceBetweenVehicle + vehicles[lastObjectIndex]->getPosition().x, startPos.y + 75);
                lastObjectIndex = firstObjectIndex;
                firstObjectIndex = (firstObjectIndex + 1) % numOfObject;
            }
            break;
        case 1:
            if(!this->isReverse() && animals[firstObjectIndex]->getPosition().x >= 0) {
                animals[lastObjectIndex]->setPosition(animals[firstObjectIndex]->getPosition().x-TableAnimal[animals[lastObjectIndex]->getType()].distanceBetweenAnimal, -20);
                firstObjectIndex = lastObjectIndex;
                lastObjectIndex = (lastObjectIndex + numOfObject - 1) % numOfObject;
            }
            if(this->isReverse() && animals[lastObjectIndex]->getPosition().x <= 2500) {
                animals[firstObjectIndex]->setPosition(TableAnimal[animals[firstObjectIndex]->getType()].distanceBetweenAnimal + animals[lastObjectIndex]->getPosition().x, -20);
                lastObjectIndex = firstObjectIndex;
                firstObjectIndex = (firstObjectIndex + 1) % numOfObject;
            }
            break;
        default:
            break;
    }
}

void RoadTheme3::setLaneVelocity(){
    
    for (auto& it:animals){
        it->setVelocity(transformVelocity(it->getVelocity()));
    }
    for (auto& it:vehicles){
        it->setVelocity(transformVelocity(it->getVelocity()));
    }
}