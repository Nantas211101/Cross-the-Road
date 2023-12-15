#include <GroundTheme2.hpp>

 GroundTheme2::GroundTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround,bool isStart)
: Ground(textureHolder, spawnPos)
, obstacles()
, typeGround(typeGround)
, isStartLane(isStart)
{
    switch (this->typeGround){
        case GroundTheme2::Lava:
            textureHolder->get(Textures::LavaGround).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::LavaGround));
            break;
        case GroundTheme2::Soil:
            textureHolder->get(Textures::Soil).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::Soil));
            break;
    }
    sf::IntRect textureRect(0, 0, widthOfLane, distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    
    buildLane();
}

void GroundTheme2::updateCurrent(sf::Time dt){}

void GroundTheme2::buildLane() {
    if(isStartLane){
        for(int j = 0; j < 4; j++) {
            std::unique_ptr<Obstacle> obstacle(new Obstacle(Obstacle::Fire, *textureHolder));
            obstacles.push_back(obstacle.get());
            if(j <=1){
                obstacle->setPosition(j * 100 + 500 + obstacle->getBoundingRect().width/2 ,0);
            }
            else{
                obstacle->setPosition((17-j) * 100 + 500 + obstacle->getBoundingRect().width/2 ,0);
            }
            this->attachChild(std::move(obstacle));
        }
    }
    else{
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(3, 7);
        int numObstacles = dist(gen);
        for(int j = 0; j < numObstacles; j++) {
            std::unique_ptr<Obstacle> obstacle(new Obstacle(Obstacle::Fire, *textureHolder));
            obstacles.push_back(obstacle.get());
            int randNum = rand() % 17;
            obstacle->setPosition( randNum * 100 , 0 );
            this->attachChild(std::move(obstacle));
        }
    }
    
}

