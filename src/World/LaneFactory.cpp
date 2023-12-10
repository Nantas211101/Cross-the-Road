#include "../../include/World/LaneFactory.h"

LaneFactory::LaneFactory(TextureHolder* textureHolder, sf::Vector2f startPos) 
: lanes()
, textureHolder(textureHolder)
, startPos(startPos)
{}

std::vector<std::unique_ptr<Lane>> LaneFactory::randomTemplateLane() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 6);
    int random = dist(gen);
    lanes.clear();
    switch(random) {
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
    std::vector<std::unique_ptr<Lane>> randLanes;
    for(auto&x : lanes) {
        randLanes.push_back(std::move(x));
    }
    return randLanes;
}

void LaneFactory::templateGround(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new GroundTheme1(textureHolder, startPos, GroundTheme1::Grass));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactory::templateRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 1;
        if (num == 1 || i == num - 1) checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme1(textureHolder, startPos, checkLine, RoadTheme1::VehicleRoad));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactory::templateAnimalRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme1(textureHolder, startPos, checkLine, RoadTheme1::AnimalRoad));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactory::templateRiver(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new RiverTheme1(textureHolder, startPos));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactory::templateRailway(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new Railway(textureHolder, startPos));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactory::templateLane1() {
    templateGround(2);
    templateRiver(2);
}

void LaneFactory::templateLane2() {
    templateGround(3);
    templateRoad(5);
}

void LaneFactory::templateLane3() {
    templateGround(1);
    templateAnimalRoad(2);
    templateRailway(1);
}

void LaneFactory::templateLane4() {
    templateGround(1);
    templateRiver(1);
    templateRailway(1);
}

void LaneFactory::templateLane5() {
    templateGround(2);
    templateRoad(4);
    templateRailway(1);
}

void LaneFactory::templateLane6() {
    templateGround(1);
    templateRailway(1);
}