#pragma once
#include <Railway.hpp>
#include <RoadTheme1.hpp>
#include <RoadTheme2.hpp>
#include <RoadTheme3.hpp>
#include <RiverTheme1.hpp>
#include <RiverTheme2.hpp>
#include <RiverTheme3.hpp>
#include <GroundTheme1.hpp>
#include <GroundTheme2.hpp>
#include <GroundTheme3.hpp>
#include <FinishLane.hpp>

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class LaneFactoryTheme1;
class LaneFactoryTheme2;
class LaneFactoryTheme3;

class LaneFactory {
friend LaneFactoryTheme1;
friend LaneFactoryTheme2;
friend LaneFactoryTheme3;
protected:
    std::vector<std::unique_ptr<Lane>> lanes;
    sf::Vector2f startPos;
    TextureHolder* textureHolder;
    int level;
private:
    void templateFinishLevel(int num);
    virtual void templateStartLane(int num) = 0;
    virtual void templateFinishTheme(int num) = 0;
    virtual void templateGround(int num) = 0;
    virtual void templateRoad(int num) = 0;
    virtual void templateAnimalRoad(int num) = 0;
    virtual void templateRiver(int num) = 0;
    virtual void templateRailway(int num) = 0;

    virtual void templateLevel1() = 0;
    virtual void templateLevel2() = 0;
    virtual void templateLevel3() = 0;
    virtual void templateLevel4() = 0;
    virtual void templateLevel5() = 0;

    void templateLane1();
    void templateLane2();
    void templateLane3();
    void templateLane4();
    void templateLane5();
    void templateLane6();
    void templateLane7();
    void templateLane8();
    void templateLane9();
    void templateLane10();
    void templateLane11();
    void templateLane12();
    void templateLane13();
    void templateLane14();
    void templateLane15();
    void templateLane16();
    void templateLane17();
    void templateLane18();
    void templateLane19();
    void templateLane20();
    void templateLane21();
    void templateLane22();
    void templateLane23();
    void templateLane24();
    void templateLane25();
    void templateLane26();
    void templateLane27();
    void templateLane28();
    void templateLane29();
    void templateLane30();
    void templateLane31();
    void templateLane32();
    void templateLane33();
    void templateLane34();
    void templateLane35();
    void templateLane36();
    void templateLane37();
    void templateLane38();
    void templateLane39();
    void templateLane40();

    void callTemplateX(int x);
public:
    LaneFactory(TextureHolder* textureHolder, sf::Vector2f startPos, int level);
    virtual ~LaneFactory(){};
    std::vector<std::unique_ptr<Lane>> templateLane();
};