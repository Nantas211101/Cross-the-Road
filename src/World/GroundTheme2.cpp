#include <GroundTheme2.hpp>

 GroundTheme2::GroundTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround,bool isStart, int difficulty)
: Ground(textureHolder, spawnPos, difficulty)
, obstacles()
, typeGround(typeGround)
, isStartLane(isStart)
{
    switch (this->typeGround){
        case GroundTheme2::Snow:
            textureHolder->get(Textures::SnowGround).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::SnowGround));
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
        int randDeco = rand()%3;
        switch (randDeco) {
            case 0:
                randType = Decorator::DecoFlower2;
                break;
            case 1:
                randType = Decorator::DecoIce1;
                break;
            case 2:
                randType = Decorator::DecoSnow1;
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
        Obstacle::Type kind;
        int tile = 0;
        while (tile < 17) {
            int randObtacle = rand()%4;
            switch (randObtacle) {
                case 0:
                    kind = Obstacle::SnowMan;
                    break;
                case 1:
                    kind = Obstacle::SnowTree1;
                    break;
                case 2:
                    kind = Obstacle::SnowTree;
                    break;
                case 3:
                    kind = Obstacle::Coin;
                    break;               
            }
            std::unique_ptr<Obstacle> obstacle(new Obstacle(kind, *textureHolder));
            obstacles.push_back(obstacle.get());
            int randNum = rand() % 7 + 1;
            tile += randNum; 
            obstacle->setPosition( tile * distanceBetweenLane + 500,0);
            this->attachChild(std::move(obstacle));
        }
    }
}

