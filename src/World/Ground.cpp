#include "../../include/World/Ground.h"

 Ground::Ground(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround)
: Lane(textureHolder, spawnPos)
, obstacles()
, typeGround(typeGround)
{
    switch (this->typeGround){
        case Ground::Grass:
            textureHolder->get(Textures::Grass).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::Grass));
            break;
        case Ground::Soil:
            textureHolder->get(Textures::Soil).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::Soil));
            break;
    }
    sf::IntRect textureRect(0, 0, 15000, distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    
    buildLane();
}

void Ground::updateCurrent(sf::Time dt) {
}

void Ground::buildLane() {
    int numObstacles = 3 + rand() % 2;
    for(int j = 0; j < numObstacles; j++) {
        std::unique_ptr<Obstacle> obstacle(new Obstacle(*textureHolder));
        obstacles.push_back(obstacle.get());
        int randNum = rand() % 10;
        obstacle->setPosition( randNum * 192 + obstacle->getBoundingRect().width/2 , startPos.y);
        this->attachChild(std::move(obstacle));
    }
}

