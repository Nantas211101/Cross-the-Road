#include <LaneFactoryTheme1.hpp>

LaneFactoryTheme1::LaneFactoryTheme1(TextureHolder* textureHolder, sf::Vector2f startPos) 
: LaneFactory(textureHolder, startPos, 1)
{}

std::vector<std::unique_ptr<Lane>> LaneFactoryTheme1::randomTemplateLane() {
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
    //templateFinishLevel(1);
    //templateFinishTheme(1);
    std::vector<std::unique_ptr<Lane>> randLanes;
    for(auto&x : lanes) {
        randLanes.push_back(std::move(x));
    }
    return randLanes;
}

std::vector<std::unique_ptr<Lane>> LaneFactoryTheme1::templateStartLane(){
    lanes.clear();
    for(int i = 0; i < 3; i++) {
        bool isStart = 1;
        std::unique_ptr<Lane> lane(new GroundTheme1(textureHolder, startPos, GroundTheme1::Grass,isStart));
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



void LaneFactoryTheme1::templateFinishTheme(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, FinishLane::Theme1));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane * 5;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateGround(int num) {
    for(int i = 0; i < num; i++) {
        bool isStart = 0;
        std::unique_ptr<Lane> lane(new GroundTheme1(textureHolder, startPos, GroundTheme1::Grass,isStart));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 1;
        if (num == 1 || i == num - 1) checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme1(textureHolder, startPos, checkLine, RoadTheme1::VehicleRoad));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateAnimalRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme1(textureHolder, startPos, checkLine, RoadTheme1::AnimalRoad));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateRiver(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new RiverTheme1(textureHolder, startPos));
        lane->setPosition(0,startPos.y);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateRailway(int num) {
    for(int i = 0; i < num; i++) {
        int kind = rand()%2;
        Railway::Type kindTrain;
        switch(kind){
            case 0:
                kindTrain = Railway::WoodTrain;
                break;
            case 1:
                kindTrain = Railway::Train1;
                break;
        }
        std::unique_ptr<Lane> lane(new Railway(textureHolder, startPos, kindTrain));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateLane1() {
    templateGround(2);
    templateRiver(2);
}

void LaneFactoryTheme1::templateLane2() {
    templateGround(3);
    templateRoad(5);
}

void LaneFactoryTheme1::templateLane3() {
    templateGround(1);
    templateAnimalRoad(2);
    templateRailway(1);
}

void LaneFactoryTheme1::templateLane4() {
    templateGround(1);
    templateRiver(2);
    templateRailway(1);
}

void LaneFactoryTheme1::templateLane5() {
    templateGround(2);
    templateRoad(4);
    templateRailway(1);
}

void LaneFactoryTheme1::templateLane6() {
    templateGround(1);
    templateRailway(1);
}
