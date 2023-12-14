#pragma once
#include <LaneFactory.hpp>

class LaneFactoryTheme2 : public LaneFactory {
private:

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

public:
    LaneFactoryTheme2(TextureHolder* textureHolder, sf::Vector2f startPos);
    
    std::vector<std::unique_ptr<Lane>> randomTemplateLane();
    std::vector<std::unique_ptr<Lane>> templateStartLane();
};