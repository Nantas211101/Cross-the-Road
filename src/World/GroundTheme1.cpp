#include <GroundTheme1.h>

 GroundTheme1::GroundTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround)
: Ground(textureHolder, spawnPos)
, obstacles()
, typeGround(typeGround)
{
    switch (this->typeGround){
        case GroundTheme1::Grass:
            textureHolder->get(Textures::Grass).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::Grass));
            break;
        case GroundTheme1::Soil:
            textureHolder->get(Textures::Soil).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::Soil));
            break;
    }
    sf::IntRect textureRect(0, 0, 15000, distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    
    buildLane();
}

void GroundTheme1::updateCurrent(sf::Time dt){}

void GroundTheme1::buildLane() {
    int numObstacles = 3 + rand() % 5;
    for(int j = 0; j < numObstacles; j++) {
        std::unique_ptr<Obstacle> obstacle(new Obstacle(Obstacle::Rock1, *textureHolder));
        obstacles.push_back(obstacle.get());
        int randNum = rand() % 10;
        obstacle->setPosition(randNum * 100 , 15);
        this->attachChild(std::move(obstacle));
    }
}

