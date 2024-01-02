#include <LaneFactoryTheme2.hpp>

LaneFactoryTheme2::LaneFactoryTheme2(TextureHolder* textureHolder, sf::Vector2f startPos, int level) 
: LaneFactory(textureHolder, startPos, level)
{}

void LaneFactoryTheme2::templateStartLane(int num){
    for(int i = 0; i < num; i++) {
        bool isStart = 1;
        std::unique_ptr<Lane> lane(new GroundTheme2(textureHolder, startPos, GroundTheme2::Snow,isStart, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateFinishTheme(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane*7;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateGround(int num) {
    for(int i = 0; i < num; i++) {
        bool isStart = 0;
        std::unique_ptr<Lane> lane(new GroundTheme2(textureHolder, startPos, GroundTheme2::Snow,isStart, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 1;
        if (num == 1 || i == num - 1) checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme2(textureHolder, startPos, checkLine, RoadTheme2::VehicleRoad, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateAnimalRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme2(textureHolder, startPos, checkLine, RoadTheme2::AnimalRoad, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateRiver(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new RiverTheme2(textureHolder, startPos, level, i%2));
        lane->setPosition(0,startPos.y);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateRailway(int num) {
    for(int i = 0; i < num; i++) {
        int kind = rand()%2;
        Railway::Type kindTrain;
        switch(kind){
            case 0:
                kindTrain = Railway::SnowTrain;
                break;
            case 1:
                kindTrain = Railway::SantaTrain;
                break;
        }
        std::unique_ptr<Lane> lane(new Railway(textureHolder, startPos, kindTrain, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateLevel1(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,2);
    int randomTemplate;
    for (int i=1; i<=6; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme2::templateLevel2(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(3,4);
    int randomTemplate;
    for (int i=1; i<=8; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme2::templateLevel3(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,4);
    int randomTemplate;
    for (int i=1; i<=12; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme2::templateLevel4(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,5);
    int randomTemplate;
    for (int i=1; i<=12; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme2::templateLevel5(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,5);
    int randomTemplate;
    for (int i=1; i<=14; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}
