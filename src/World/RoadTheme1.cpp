#include <RoadTheme1.h>

RoadTheme1::RoadTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos, bool checkLine, Type typeRoad)
:Road(textureHolder, spawnPos),
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

    firstObjectIndex = 0;
    lastObjectIndex = numOfObject - 1;
}

void RoadTheme1::generateAnimal(){
    int distance = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 2);
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
    
    std::uniform_int_distribution<int> dist2(0, 199);
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
        animal->setPosition(randSpawnPos + distance, 0);
        distance += TableAnimal[kind].distanceBetweenAnimal;
        animals.push_back(animal.get());
        this->attachChild(std::move(animal));
    }
}

void RoadTheme1::generateVehicle(){
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

    std::uniform_int_distribution<int> dist1(0, 199);
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
        vehicle->setPosition(randSpawnPos + distance, 50);
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
         traff->setPosition(1900, 0);
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
            vehicles[lastObjectIndex]->setPosition(-TableVehicle[vehicles[lastObjectIndex]->getType()].distanceBetweenVehicle, 50);
            firstObjectIndex = lastObjectIndex;
            lastObjectIndex = (lastObjectIndex + numOfObject - 1) % numOfObject;
        }
        if(this->isReverse() && vehicles[lastObjectIndex]->getPosition().x <= 2500) {
            vehicles[firstObjectIndex]->setPosition(TableVehicle[vehicles[firstObjectIndex]->getType()].distanceBetweenVehicle + 2500, 50);
            lastObjectIndex = firstObjectIndex;
            firstObjectIndex = (firstObjectIndex + 1) % numOfObject;
        }
    }
    else{
        if(!this->isReverse() && animals[firstObjectIndex]->getPosition().x >= 0) {
            animals[lastObjectIndex]->setPosition(-TableAnimal[animals[lastObjectIndex]->getType()].distanceBetweenAnimal, 0);
            firstObjectIndex = lastObjectIndex;
            lastObjectIndex = (lastObjectIndex + numOfObject - 1) % numOfObject;
        }
        if(this->isReverse() && animals[lastObjectIndex]->getPosition().x <= 2500) {
            animals[firstObjectIndex]->setPosition(TableAnimal[animals[firstObjectIndex]->getType()].distanceBetweenAnimal + 2500, 0);
            lastObjectIndex = firstObjectIndex;
            firstObjectIndex = (firstObjectIndex + 1) % numOfObject;
        }
    }
}