#include "../../include/World/Railway.h"

namespace {
    const std::vector<TrainData> TableTrain = initializeTrainData();
}

// 50: width each lane

void Railway::loadTexture(){
    textureHolder.load(Textures::Railway, "../../Media/Textures/Railway.png");
    //textureHolder.load(Textures::Traffic, "../../Media/Textures/Traffic.png");
    textureHolder.load(Textures::Train1, "../../Media/Textures/Train1.png");
    textureHolder.load(Textures::Train2, "../../Media/Textures/Train2.png");
    textureHolder.load(Textures::Train3, "../../Media/Textures/Train3.png");
}

Railway::Railway(sf::Vector2f spawnPos)
: Lane()
// ,hasTraffic(1)
, startPos(spawnPos) {
    loadTexture();
    textureHolder.get(Textures::Railway).setRepeated(true);
    sprite.setTexture(textureHolder.get(Textures::Railway));
    sf::IntRect textureRect(0, 0, 3000, 152);
    //sprite.scale(0.5f,0.6f);
    sprite.setTextureRect(textureRect);
    generateTrain();
}
void Railway::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}

void Railway::updateCurrent(sf::Time dt){

}

void Railway::generateTrain(){
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

     std::unique_ptr<Train> train(new Train(kind, textureHolder));
    train->setVelocity(1.0 * TableTrain[kind].speed, 0);
    train->scale(TableTrain[kind].scaling.x,TableTrain[kind].scaling.y);

    train->setPosition(-800, startPos.y - 120);
    this->attachChild(std::move(train));
}