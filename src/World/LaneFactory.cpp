#include "../../include/World/LaneFactory.h"

LaneFactory::LaneFactory(sf::Vector2f startPos) 
: lanes()
, startPos(startPos)
{}

std::vector<std::unique_ptr<Lane>> LaneFactory::randomTemplateLane() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5);
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
    }
    std::vector<std::unique_ptr<Lane>> randLanes;
    for(auto&x : lanes) {
        randLanes.push_back(std::move(x));
    }
    return randLanes;
}

void LaneFactory::templateGrass(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new Grass(startPos));
        lane->setPosition(startPos);
        startPos.y -= 150;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactory::templateRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 1;
        if (num == 1 || i == num - 1) checkLine = 0;
        std::unique_ptr<Lane> lane(new Road(startPos, checkLine));
        lane->setPosition(startPos);
        startPos.y -= 150;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactory::templateRiver(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new River(startPos));
        lane->setPosition(startPos);
        startPos.y -= 150;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactory::templateLane1() {
    templateGrass(2);
    templateRiver(2);
}

void LaneFactory::templateLane2() {
    templateGrass(3);
    templateRoad(5);
}

void LaneFactory::templateLane3() {
    templateGrass(1);
    templateRoad(2);
}

void LaneFactory::templateLane4() {
    templateGrass(1);
    templateRiver(1);
}

void LaneFactory::templateLane5() {
    templateGrass(2);
    templateRoad(4);
}