#include <GroundTheme3.hpp>

 GroundTheme3::GroundTheme3(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround,bool isStart)
: Ground(textureHolder, spawnPos)
, obstacles()
, typeGround(typeGround)
, isStartLane(isStart)
{
    switch (this->typeGround){
        case GroundTheme3::Snow:
            textureHolder->get(Textures::SnowGround).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::SnowGround));
            break;
        case GroundTheme3::Soil:
            textureHolder->get(Textures::Soil).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::Soil));
            break;
    }
    sf::IntRect textureRect(0, 0, widthOfLane, distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    
    buildLane();
}

void GroundTheme3::updateCurrent(sf::Time dt){}

void GroundTheme3::buildLane() {

    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<int> dist2(0,5);
    int numDecorators = dist2(gen2);
    Decorator::Type randType;
    for(int j = 0; j < numDecorators; j++) {
        int randDeco = rand()%3;
        switch (randDeco) {
            case 0:
                randType = Decorator::DecoTree1;
                break;
            case 1:
                randType = Decorator::DecoTree2;
                break;
            case 2:
                randType = Decorator::DecoFlower1;
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
            std::unique_ptr<Obstacle> obstacle(new Obstacle(Obstacle::SnowTree, *textureHolder));
            obstacles.push_back(obstacle.get());
            if(j <=1){
                obstacle->setPosition(j * 100 + 500,-15);
            }
            else{
                obstacle->setPosition((18-j) * 100 + 500,-15);
            }
            this->attachChild(std::move(obstacle));
        }
    }
    else{
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(3, 7);
        int numObstacles = dist(gen);
        Obstacle::Type kind;
        int randObtacle = rand()%2;
        switch (randObtacle) {
            case 0:
                kind = Obstacle::SnowMan;
                break;
            case 1:
                kind = Obstacle::SnowTree;
                break;
        }
        for(int j = 0; j < numObstacles; j++) {
            std::unique_ptr<Obstacle> obstacle(new Obstacle(kind, *textureHolder));
            obstacles.push_back(obstacle.get());
            int randNum = rand() % 17;
            obstacle->setPosition( randNum * 100 + 500,0);
            this->attachChild(std::move(obstacle));
        }
    }
}

