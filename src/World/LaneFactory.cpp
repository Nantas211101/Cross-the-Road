#include <LaneFactory.hpp>

LaneFactory::LaneFactory(TextureHolder* textureHolder, sf::Vector2f startPos, int level)
: lanes()
, textureHolder(textureHolder)
, startPos(startPos)
, level(level)
{}
#include <iostream>
std::vector<std::unique_ptr<Lane>> LaneFactory::templateLane() {
    lanes.clear();
    templateStartLane(3);
    int caseLevel = level;
    while (caseLevel>5){
        caseLevel -=5 ;
    }
    switch(caseLevel) {
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
    if (caseLevel == 5) templateFinishTheme(1);
    else templateFinishLevel(1); 
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

// TEMPLATE GROUND
void LaneFactory::templateLane1() {
    templateGround(2);
}
void LaneFactory::templateLane2() {
    templateGround(3);
    templateRiver(1);
}
void LaneFactory::templateLane3() {
    templateRiver(1);
    templateGround(4);
    templateAnimalRoad(2);
}

// TEMPLATE ANIMAL ROAD
//    __EASY__:
void LaneFactory::templateLane4() {
    templateGround(1);
    templateAnimalRoad(2);
    templateGround(1);
}
void LaneFactory::templateLane5() {
    templateGround(1);
    templateAnimalRoad(3);
    templateGround(1);
}
void LaneFactory::templateLane6() {
    templateAnimalRoad(1);
}
//    __MEDIUM__:
void LaneFactory::templateLane7() {
    templateGround(2);
    templateAnimalRoad(4);
    templateGround(1);
}
void LaneFactory::templateLane8() {
    templateAnimalRoad(2);
}
void LaneFactory::templateLane9() {
    templateAnimalRoad(3);
    templateGround(1);
}
//    __HARD__:
void LaneFactory::templateLane10() {
    templateGround(1);
    templateAnimalRoad(4);
    templateRiver(1);
    templateGround(2);
}
void LaneFactory::templateLane11() {
    templateRiver(2);
    templateAnimalRoad(3);
    templateGround(2);
}
void LaneFactory::templateLane12() {
    templateGround(2);
    templateAnimalRoad(4);
    templateGround(1);
}
void LaneFactory::templateLane13() {
    templateRiver(1);
    templateAnimalRoad(3);
    templateRiver(2);
    templateGround(1);
}

// TEMPLATE ROAD
//    __EASY__:
void LaneFactory::templateLane14() {
    templateRoad(1);
}
void LaneFactory::templateLane15() {
    templateGround(1);
    templateRoad(2);
    templateGround(1);
}
void LaneFactory::templateLane16() {
    templateRiver(1);
    templateRoad(3);
    templateGround(1);
}
//  __MEDIUM__:
void LaneFactory::templateLane17() {
    templateGround(1);
    templateRoad(3);
    templateRiver(2);
    templateGround(2);
}
void LaneFactory::templateLane18() {
    templateGround(2);
    templateRoad(4);
    templateGround(1);
}
void LaneFactory::templateLane19() {
    templateRoad(2);
    templateAnimalRoad(2);
    templateGround(1);
}
//  __HARD__:
void LaneFactory::templateLane20() {
    templateGround(2);
    templateRoad(4);
    templateGround(1);
}
void LaneFactory::templateLane21() {
    templateGround(2);
    templateRoad(4);
    templateRiver(3);
    templateGround(1);
}
void LaneFactory::templateLane22() {
    templateAnimalRoad(1);
    templateRoad(2);
    templateGround(1);
}

// TEMPLATE RIVER
//    __EASY__:
void LaneFactory::templateLane23() {
    templateRiver(1);
}
void LaneFactory::templateLane24() {
    templateGround(1);
    templateRiver(2);
    templateRoad(1);
}
void LaneFactory::templateLane25() {
    templateGround(1);
    templateRiver(3);
    templateGround(2);
}

//    __MEDIUM__:
void LaneFactory::templateLane26() {
    templateGround(1);
    templateAnimalRoad(3);
    templateGround(1);
}
void LaneFactory::templateLane27() {
    templateGround(1);
    templateRiver(3);
    templateRoad(1);
}
void LaneFactory::templateLane28() {
    templateRoad(1);
    templateRiver(3);
    templateGround(2);
}

//    __HARD__:
void LaneFactory::templateLane29() {
    templateGround(1);
    templateRiver(3);
    templateGround(2);
}
void LaneFactory::templateLane30() {
    templateGround(2);
    templateRoad(2);
    templateRiver(2);
    templateGround(1);
}
void LaneFactory::templateLane31() {
    templateRiver(2);
    templateRoad(2);
    templateRiver(1);
}
void LaneFactory::templateLane32() {
    templateRailway(1);
    templateGround(1);
    templateRiver(3);
    templateGround(1);
}

// TEMPLATE RAILWAY
void LaneFactory::templateLane33() {
    templateGround(1);
    templateRailway(1);
}
void LaneFactory::templateLane34() {
    templateGround(1);
    templateRailway(1);
}
void LaneFactory::templateLane35() {
    templateRailway(2);
    templateGround(2);
}

// TEMPLATE HARD FOR THEME 3
void LaneFactory::templateLane36() {
    templateRiver(1);
    templateRoad(6);
    templateGround(3);
}
void LaneFactory::templateLane37() {
    templateRiver(5);
    templateRoad(4);
    templateGround(2);
}
void LaneFactory::templateLane38() {
    templateGround(3);
    templateRoad(10);
    templateGround(3);
}
void LaneFactory::templateLane39() {
    templateRiver(2);
    templateRoad(5);
    templateGround(2);
}
void LaneFactory::templateLane40() {
    templateGround(2);
    templateRoad(8);
    templateGround(2);
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
        case 29:
            templateLane29();
            break;
        case 30:
            templateLane30();
            break;
        case 31:
            templateLane31();
            break;
        case 32:
            templateLane32();
            break;
        case 33:
            templateLane33();
            break;
        case 34:
            templateLane34();
            break;
        case 35:
            templateLane35();
            break;
        case 36:
            templateLane36();
            break;
        case 37:
            templateLane37();
            break;
        case 38:
            templateLane38();
            break;
        case 39:
            templateLane39();
            break;
        case 40:
            templateLane40();
            break;
        default:
            break;
    }
}