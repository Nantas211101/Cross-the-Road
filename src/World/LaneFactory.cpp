#include <LaneFactory.hpp>

LaneFactory::LaneFactory(TextureHolder* textureHolder, sf::Vector2f startPos, int level)
: lanes()
, textureHolder(textureHolder)
, startPos(startPos)
, level(level)
{}

std::vector<std::unique_ptr<Lane>> LaneFactory::templateLane() {
    lanes.clear();
    templateStartLane(3);
    switch(level) {
    case 1:
        templateLevel1();
        break;
    case 2:
        templateLevel2();
        break;
    case 3:
        templateLevel3();
        break;
    case 4:
        templateLevel4();
        break;
    case 5:
        templateLevel5();
        break;
    }
    templateFinishLevel(1);
    if (level == 5) templateFinishTheme(1);
    std::vector<std::unique_ptr<Lane>> randLanes;
    for(auto&x : lanes) {
        randLanes.push_back(std::move(x));
    }
    return randLanes;
}

void LaneFactory::templateFinishLevel(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, level, 1));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane * 3;
        lanes.push_back(std::move(lane));
    }
}



// -----------------TEMPLATE's WORLD------------------
// VERY EASY TEMPLATE  (only 1 ROAD or RIVER)
void LaneFactory::templateLane1() {
    templateGround(2);
    templateRiver(1);
}

void LaneFactory::templateLane2() {
    templateGround(2);
    templateAnimalRoad(1);
}

void LaneFactory::templateLane3() {
    templateGround(1);
    templateRoad(1);
    templateGround(1);
}

void LaneFactory::templateLane4() {
    templateGround(1);
    templateRoad(1);
    templateGround(1);
}

void LaneFactory::templateLane5() {
    templateGround(2);
    templateAnimalRoad(1);
}

// EASY TEMPLATE (1 RAILWAY || 2 ROAD or RIVER)

// + donot use all of 6,7,8 at the same time
void LaneFactory::templateLane6() {
    templateGround(1);
    templateRoad(1);
    templateGround(1);
    templateRoad(1);
}

void LaneFactory::templateLane7() {
    templateRiver(1);
    templateGround(1);
    templateRiver(1);
    templateGround(1);
}

void LaneFactory::templateLane8() {
    templateGround(1);
    templateRiver(1);
    templateGround(1);
    templateRoad(1);
}

void LaneFactory::templateLane9() {
    templateGround(2);
    templateRailway(1);
}

void LaneFactory::templateLane10() {
    templateGround(2);
    templateAnimalRoad(2);
}

void LaneFactory::templateLane11() {
    templateGround(2);
    templateRoad(2);
}

void LaneFactory::templateLane12() {
    templateGround(2);
    templateRoad(2);
}

void LaneFactory::templateLane13() {
    templateRiver(1);
    templateGround(1);
    templateAnimalRoad(1);
    templateRoad(1);
    templateGround(1);
}

void LaneFactory::templateLane14() {
    templateGround(2);
    templateRiver(2);
}
//RAILWAY TEMPLATE
void LaneFactory::templateLane15() {
    templateRailway(1);
}
void LaneFactory::templateLane16() {
    templateRailway(2);
    templateGround(1);
}
void LaneFactory::templateLane17() {
    templateRiver(1);
    templateRailway(1);
    templateGround(1);
}

//MEDIUM TEMPLATE (~3 ROAD or RIVER or RAILWAY)
void LaneFactory::templateLane18() {
    templateGround(2);
    templateAnimalRoad(1);
    templateRoad(2);
}
void LaneFactory::templateLane19() {
    templateRoad(2);
    templateRailway(1);
    templateGround(1);
}
void LaneFactory::templateLane20() {
    templateRiver(1);
    templateRailway(1);
    templateGround(1);
}
void LaneFactory::templateLane21() {
    templateRiver(3);
    templateGround(2);
}
void LaneFactory::templateLane22() {
    templateAnimalRoad(3);
    templateGround(1);
}
void LaneFactory::templateLane23() {
    templateRoad(3);
    templateGround(1);
}
void LaneFactory::templateLane24() {
    templateRiver(2);
}
void LaneFactory::templateLane25() {
    templateAnimalRoad(2);
}

//HARD1 TEMPLATE (~4 ROAD or RIVER or RAILWAY)
void LaneFactory::templateLane26() {
    templateRiver(2);
    templateRoad(2);
}
void LaneFactory::templateLane27() {
    templateAnimalRoad(4);
    templateGround(1);
}
void LaneFactory::templateLane28() {
    templateRiver(4);
}
void LaneFactory::callTemplateX(int x){
    switch(x){
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
        case 7:
            templateLane7();
            break;
        case 8:
            templateLane8();
            break;
        case 9:
            templateLane9();
            break;
        case 10:
            templateLane10();
            break;
        case 11:
            templateLane11();
            break;
        case 12:
            templateLane12();
            break;
        case 13:
            templateLane13();
            break;
        case 14:
            templateLane14();
            break;
        case 15:
            templateLane15();
            break;
        case 16:
            templateLane16();
            break;
        case 17:
            templateLane17();
            break;
        case 18:
            templateLane18();
            break;
        case 19:
            templateLane19();
            break;
        case 20:
            templateLane20();
            break;
        case 21:
            templateLane21();
            break;
        case 22:
            templateLane22();
            break;
        case 23:
            templateLane23();
            break;
        case 24:
            templateLane24();
            break;
        case 25:
            templateLane25();
            break;
        case 26:
            templateLane26();
            break;
        case 27:
            templateLane27();
            break;
        case 28:
            templateLane28();
            break;
        default:
            break;
    }
}