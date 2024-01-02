#include <LaneFactoryTheme3.hpp>

LaneFactoryTheme3::LaneFactoryTheme3(TextureHolder* textureHolder, sf::Vector2f startPos, int level) 
: LaneFactory(textureHolder, startPos, level)
{}

void LaneFactoryTheme3::templateStartLane(int num){
    for(int i = 0; i < num; i++) {
        bool isStart = 1;
        std::unique_ptr<Lane> lane(new GroundTheme3(textureHolder, startPos, GroundTheme3::Lava,isStart, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateFinishTheme(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane * 8;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateGround(int num) {
    for(int i = 0; i < num; i++) {
        bool isStart = 0;
        std::unique_ptr<Lane> lane(new GroundTheme3(textureHolder, startPos, GroundTheme3::Lava,isStart, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 1;
        if (num == 1 || i == num - 1) checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme3(textureHolder, startPos, checkLine, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateAnimalRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme3(textureHolder, startPos, checkLine, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateRiver(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new RiverTheme3(textureHolder, startPos, level, i%2));
        lane->setPosition(0,startPos.y);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateRailway(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new Railway(textureHolder, startPos, Railway::LavaTrain, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateLevel1(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,2);
    int randomTemplate;
    for (int i=1; i<=6; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme3::templateLevel2(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(3,4);
    int randomTemplate;
    for (int i=1; i<=8; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme3::templateLevel3(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,4);
    int randomTemplate;
    for (int i=1; i<=12; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme3::templateLevel4(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,5);
    int randomTemplate;
    for (int i=1; i<=12; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme3::templateLevel5(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,5);
    int randomTemplate;
    for (int i=1; i<=14; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}
