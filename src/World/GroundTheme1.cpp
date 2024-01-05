#include <GroundTheme1.hpp>

 GroundTheme1::GroundTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround,bool isStart, int difficulty)
: Ground(textureHolder, spawnPos, difficulty)
, obstacles()
, typeGround(typeGround)
, isStartLane(isStart)
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
    sf::IntRect textureRect(0, 0, widthOfLane, distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    
    buildLane();
}

void GroundTheme1::updateCurrent(sf::Time dt){}

void GroundTheme1::buildLane() {

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
            std::unique_ptr<Obstacle> obstacle(new Obstacle(Obstacle::Tree3, *textureHolder));
            obstacles.push_back(obstacle.get());
            if(j <=1){
                obstacle->setPosition(j * distanceBetweenLane + 500 ,0);
            }
            else{
                obstacle->setPosition((18-j) * distanceBetweenLane + 500,0);
            }
            this->attachChild(std::move(obstacle));
        }
    }
    else{
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(2, 5);
        int numObstacles = dist(gen);
        Obstacle::Type kind;
        int tile = 0;
        while (tile < 17) {
            int randObtacle = rand()%8;
            switch (randObtacle) {
                case 0:
                    kind = Obstacle::Rock1;
                    break;
                case 1:
                    kind = Obstacle::Ruin1;
                    break;
                case 2:
                    kind = Obstacle::Ruin2;
                    break;
                case 3:
                    kind = Obstacle::Tree3;
                    break;
                case 4:
                    kind = Obstacle::Tree3;
                    break;
                case 5:
                    kind = Obstacle::Tree3;
                    break;   
                case 6:
                    kind = Obstacle::Rock1;
                    break;   
                case 7:
                    kind = Obstacle::Tree3;
                    break;             
            }
            std::unique_ptr<Obstacle> obstacle(new Obstacle(kind, *textureHolder));
            obstacles.push_back(obstacle.get());
            int randNum = rand() % 8 + 1;
            tile += randNum; 
            obstacle->setPosition( tile * distanceBetweenLane + 500,0);
            this->attachChild(std::move(obstacle));
        }
    }
}

