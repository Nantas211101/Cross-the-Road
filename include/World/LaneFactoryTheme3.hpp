#pragma once
#include <LaneFactory.hpp>

class LaneFactoryTheme3 : public LaneFactory {
private:

    void templateLevelFinish1(int num);
    void templateLevelFinish2(int num);
    void templateLevelFinish3(int num);
    void templateFinishTheme(int num);
    void templateGround(int num);
    void templateRoad(int num);
    void templateAnimalRoad(int num);
    void templateRiver(int num);
    void templateRailway(int num);

    void templateLane1();
    void templateLane2();
    void templateLane3();
    void templateLane4();
    void templateLane5();
    void templateLane6();
    void templateFinishLevel();

public:
    LaneFactoryTheme3(TextureHolder* textureHolder, sf::Vector2f startPos);
    
    std::vector<std::unique_ptr<Lane>> randomTemplateLane();
    std::vector<std::unique_ptr<Lane>> templateStartLane();
};