#pragma once
#include <LaneFactory.hpp>

class LaneFactoryTheme1 : public LaneFactory {
private:

    void templateStartLane(int num);
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

    void templateLevel1();
    void templateLevel2();
    void templateLevel3();
    void templateLevel4();
    void templateLevel5();

    void callTemplateX(int x);

public:
    LaneFactoryTheme1(TextureHolder* textureHolder, sf::Vector2f startPos, int level);
    
    std::vector<std::unique_ptr<Lane>> templateLane();
};