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
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<int> dist2(0,5);
    int numDecorators = dist2(gen2);
    Decorator::Type randType;
    for(int j = 0; j < numDecorators; j++) {
        int randDeco = rand()%7;
        switch (randDeco) {
            case 0:
                randType = Decorator::DecoStone;
                break;
            case 1:
                randType = Decorator::Skullcap1;
                break;
            case 2:
                randType = Decorator::Skullcap2;
                break;
            case 3:
                randType = Decorator::DeadSign;
                break;
            case 4:
                randType = Decorator::Gemstone1;
                break;
            case 5:
                randType = Decorator::Gemstone2;
                break;
            case 6:
                randType = Decorator::Gemstone3;
                break;
        }
        std::unique_ptr<Decorator> decorator(new Decorator(randType, *textureHolder));
        decorators.push_back(decorator.get());
        int randNum = rand() % 1700;
        decorator->setPosition( randNum + decorator->getBoundingRect().width/2 , 0);
        this->attachChild(std::move(decorator));
    }

    if(isStartLane){
        for(int j = 0; j < 4; j++) {
            std::unique_ptr<Obstacle> obstacle(new Obstacle(Obstacle::Volcano, *textureHolder));
            obstacles.push_back(obstacle.get());
            if(j <=1){
                obstacle->setPosition(j * 100 + 500,0);
            }
            else{
                obstacle->setPosition((18-j) * 100 + 500,0);
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
            std::unique_ptr<Obstacle> obstacle(new Obstacle(Obstacle::Volcano, *textureHolder));
            obstacles.push_back(obstacle.get());
            int randNum = rand() % 17;
            obstacle->setPosition( randNum * 100 + 500 , 0 );
            this->attachChild(std::move(obstacle));
        }
    }
    
}

