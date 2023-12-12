#include "../../include/World/Railway.h"

namespace {
    const std::vector<TrainData> TableTrain = initializeTrainData();
}

// 50: width each lane

Railway::Railway(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: Lane(textureHolder, spawnPos)
{
    textureHolder->get(Textures::Railway).setRepeated(true);
    sprite.setTexture(textureHolder->get(Textures::Railway));
    sf::IntRect textureRect(0, 0, 3000, distanceBetweenLane);
    //sprite.scale(0.5f,0.6f);
    sprite.setTextureRect(textureRect);
    buildLight();
    buildLane();
}

void Railway::updateCurrent(sf::Time dt){
    switch (railwayLight->getRailwayLightState())
    {
    case 0:
        train->setVelocity(0,0);
        break;
    
    case 1:
        train->setVelocity(1.0 * TableTrain[train->getType()].speed, 0);
        break;
    }
}

void Railway::buildLane(){
    int distance = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 3);
    int randomKindTrain = dist(gen);
    Train::Type kind;
    switch(4) {
    case 1:
        kind = Train::Train1;
        break;
    case 2:
        kind = Train::Train2;
        break;
    case 3:
        kind = Train::Train3;
        break;
     case 4:
        kind = Train::Train4;
        break;
    default:
        break;
    }

    std::unique_ptr<Train> newTrain(new Train(kind, *textureHolder));
    train = newTrain.get();
    newTrain->setVelocity(1.0 * TableTrain[kind].speed, 0);
    newTrain->scale(TableTrain[kind].scaling.x,TableTrain[kind].scaling.y);

    newTrain->setPosition(-1100, startPos.y - 100);
    this->attachChild(std::move(newTrain));
}

void Railway::buildLight(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 8);
    
    int randomKindVehicle = dist(gen);
    std::unique_ptr<RailwayLight> light(new RailwayLight(*textureHolder));
    railwayLight= light.get();
    light->setPosition(startPos.x+700,startPos.y + 30);
    this->attachChild(std::move(light));
}