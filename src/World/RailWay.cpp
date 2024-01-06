#include <Railway.hpp>

namespace {
    const std::vector<TrainData> TableTrain = initializeTrainData();
}

Railway::Railway(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type type, int difficulty)
: Lane(textureHolder, spawnPos, difficulty),
type(type)
{
    textureHolder->get(Textures::Railway).setRepeated(true);
    sprite.setTexture(textureHolder->get(Textures::Railway));
    sf::IntRect textureRect(0, 0, widthOfLane, distanceBetweenLane);
    //sprite.scale(0.5f,0.6f);
    sprite.setTextureRect(textureRect);
    
    buildLane();
    buildLight();
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
    if(train->getPosition().x >= 2200){
        train->setPosition(-800, -30);
        railwayLight->setTimeCount();
    }
}

void Railway::buildLane(){
    Train::Type kind;
    switch(type) {
    case Type::Train1:
        kind = Train::Train1;
        break;
    case Type::SnowTrain:
        kind = Train::SnowTrain;
        break;
    case Type::WoodTrain:
        kind = Train::WoodTrain;
        break;
    case Type::LavaTrain:
        kind = Train::LavaTrain;
        break;
    case Type::SantaTrain:
        kind = Train::SantaTrain;
        break;
    }

    std::unique_ptr<Train> newTrain(new Train(kind, *textureHolder));
    train = newTrain.get();
    newTrain->setVelocity(1.0 * TableTrain[kind].speed, 0);
    newTrain->scale(TableTrain[kind].scaling);

    newTrain->setPosition(-800,-30);
    this->attachChild(std::move(newTrain));
}

void Railway::buildLight(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 8);
    
    int randomKindVehicle = dist(gen);
    std::unique_ptr<RailwayLight> light(new RailwayLight(*textureHolder));
    railwayLight= light.get();
    light->setPosition(700, 30);
    this->attachChild(std::move(light));
}

void Railway::setLaneVelocity(){
    train->setVelocity(transformVelocity(train->getVelocity()));
}