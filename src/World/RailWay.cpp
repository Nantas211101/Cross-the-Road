#include <Railway.hpp>

namespace {
    const std::vector<TrainData> TableTrain = initializeTrainData();
}

Railway::Railway(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: Lane(textureHolder, spawnPos)
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
    if(train->getPosition().x >= 2500){
        train->setPosition(-300, -100);
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

    newTrain->setPosition(-300, -100);
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