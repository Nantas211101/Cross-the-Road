#include <LaneFactoryTheme2.hpp>

LaneFactoryTheme2::LaneFactoryTheme2(TextureHolder* textureHolder, sf::Vector2f startPos) 
: LaneFactory(textureHolder, startPos, 2)
{}

std::vector<std::unique_ptr<Lane>> LaneFactoryTheme2::randomTemplateLane() {
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
    templateFinishLevel(1);
    templateFinishTheme(1);
    std::vector<std::unique_ptr<Lane>> randLanes;
    for(auto&x : lanes) {
        randLanes.push_back(std::move(x));
    }
    return randLanes;
}

std::vector<std::unique_ptr<Lane>> LaneFactoryTheme2::templateStartLane(){
    lanes.clear();
    for(int i = 0; i < 3; i++) {
        bool isStart = 1;
        std::unique_ptr<Lane> lane(new GroundTheme2(textureHolder, startPos, GroundTheme2::Lava,isStart));
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

void LaneFactoryTheme2::templateFinishTheme(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, FinishLane::Theme2));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane * 8;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateGround(int num) {
    for(int i = 0; i < num; i++) {
        bool isStart = 0;
        std::unique_ptr<Lane> lane(new GroundTheme2(textureHolder, startPos, GroundTheme2::Lava,isStart));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 1;
        if (num == 1 || i == num - 1) checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme2(textureHolder, startPos, checkLine));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateAnimalRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme2(textureHolder, startPos, checkLine));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateRiver(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new RiverTheme2(textureHolder, startPos));
        lane->setPosition(0,startPos.y);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateRailway(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new Railway(textureHolder, startPos));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme2::templateLane1() {
    templateGround(2);
    templateRiver(2);
}

void LaneFactoryTheme2::templateLane2() {
    templateGround(3);
    templateAnimalRoad(2);
}

void LaneFactoryTheme2::templateLane3() {
    templateGround(1);
    templateAnimalRoad(2);
    templateRailway(1);
}

void LaneFactoryTheme2::templateLane4() {
    templateGround(1);
    templateRiver(1);
}

void LaneFactoryTheme2::templateLane5() {
    templateGround(2);
    templateRoad(4);
    templateRailway(1);
}

void LaneFactoryTheme2::templateLane6() {
    templateGround(1);
    templateRailway(1);
}