#include <LaneFactoryTheme3.hpp>

LaneFactoryTheme3::LaneFactoryTheme3(TextureHolder* textureHolder, sf::Vector2f startPos) 
: LaneFactory(textureHolder, startPos, 1)
{}

std::vector<std::unique_ptr<Lane>> LaneFactoryTheme3::randomTemplateLane() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 6);
    int random = dist(gen);
    lanes.clear();
    switch(1) {
    case 1:
        templateLane1();
        break;
    case 2:
        templateLane2();
        break;
    case 3:
        templateLane3();
        break;
    case 4:
        templateLane4();
        break;
    case 5:
        templateLane5();
        break;
    case 6:
        templateLane6();
        break;
    }
    // templateFinishLevel();
    std::vector<std::unique_ptr<Lane>> randLanes;
    for(auto&x : lanes) {
        randLanes.push_back(std::move(x));
    }
    return randLanes;
}

std::vector<std::unique_ptr<Lane>> LaneFactoryTheme3::templateStartLane(){
    lanes.clear();
    for(int i = 0; i < 3; i++) {
        bool isStart = 1;
        std::unique_ptr<Lane> lane(new GroundTheme3(textureHolder, startPos, GroundTheme3::Snow,isStart));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
    std::vector<std::unique_ptr<Lane>> randLanes;
    for(auto&x : lanes) {
        randLanes.push_back(std::move(x));
    }
    return randLanes;
}

void LaneFactoryTheme3::templateLevelFinish(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, FinishLane::Level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateFinishTheme(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, FinishLane::Theme3));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateGround(int num) {
    for(int i = 0; i < num; i++) {
        bool isStart = 0;
        std::unique_ptr<Lane> lane(new GroundTheme3(textureHolder, startPos, GroundTheme3::Snow,isStart));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 1;
        if (num == 1 || i == num - 1) checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme3(textureHolder, startPos, checkLine, RoadTheme3::VehicleRoad));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateAnimalRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme3(textureHolder, startPos, checkLine, RoadTheme3::AnimalRoad));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateRiver(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new RiverTheme3(textureHolder, startPos));
        lane->setPosition(0,startPos.y);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateRailway(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new Railway(textureHolder, startPos));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateLane1() {
    templateGround(2);
    templateRiver(2);
    templateRoad(2);
    templateRailway(1);
    templateAnimalRoad(2);
}

void LaneFactoryTheme3::templateLane2() {
    templateGround(3);
    templateRoad(5);
}

void LaneFactoryTheme3::templateLane3() {
    templateGround(1);
    templateAnimalRoad(2);
    templateRailway(1);
}

void LaneFactoryTheme3::templateLane4() {
    templateGround(1);
    templateRiver(2);
    templateRailway(1);
}

void LaneFactoryTheme3::templateLane5() {
    templateGround(2);
    templateRoad(4);
    templateRailway(1);
}

void LaneFactoryTheme3::templateLane6() {
    templateGround(1);
    templateRailway(1);
}

void LaneFactoryTheme3::templateFinishLevel(){
    templateLevelFinish(1);
}