#include "../../include/World/Railway.h"

namespace {
    const std::vector<TrainData> TableTrain = initializeTrainData();
}

// 50: width each lane

Railway::Railway(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: Lane()
, textureHolder(textureHolder)
, startPos(spawnPos) {
    textureHolder->get(Textures::Railway).setRepeated(true);
    sprite.setTexture(textureHolder->get(Textures::Railway));
    sf::IntRect textureRect(0, 0, 3000, distanceBetweenLane);
    //sprite.scale(0.5f,0.6f);
    sprite.setTextureRect(textureRect);
    buildLight();
    buildLane();
}
void Railway::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}

void Railway::updateCurrent(sf::Time dt){
    switch (railwayLight->getRailwayLightState())
    {
    case 0:
        train->setVelocity(0,0);
        break;
    
    case 2:
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
    switch(randomKindTrain) {
    case 1:
        kind = Train::Train1;
        break;
    case 2:
        kind = Train::Train2;
        break;
    case 3:
        kind = Train::Train3;
        break;
    default:
        break;
    }

    std::unique_ptr<Train> newTrain(new Train(kind, *textureHolder));
    train = newTrain.get();
    newTrain->setVelocity(1.0 * TableTrain[kind].speed, 0);
    newTrain->scale(TableTrain[kind].scaling.x,TableTrain[kind].scaling.y);

    newTrain->setPosition(-1500, startPos.y - 120);
    this->attachChild(std::move(newTrain));
}

void Railway::buildLight(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 8);
    
    int randomKindVehicle = dist(gen);
    std::unique_ptr<RailwayLight> light(new RailwayLight(*textureHolder));
    railwayLight= light.get();
    light->setPosition(startPos.x+600,startPos.y + 75);
    this->attachChild(std::move(light));
}