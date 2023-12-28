#pragma once
#include <LaneFactory.hpp>

class LaneFactoryTheme3 : public LaneFactory {
private:

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

public:
    LaneFactoryTheme3(TextureHolder* textureHolder, sf::Vector2f startPos, int level);
    
    std::vector<std::unique_ptr<Lane>> templateLane();
    std::vector<std::unique_ptr<Lane>> templateStartLane();
    std::vector<std::unique_ptr<Lane>> generateLane1();
    std::vector<std::unique_ptr<Lane>> generateLane2();
    std::vector<std::unique_ptr<Lane>> generateLane3();
    std::vector<std::unique_ptr<Lane>> generateLane4();
    std::vector<std::unique_ptr<Lane>> generateLane5();
    std::vector<std::unique_ptr<Lane>> generateLane6();
};