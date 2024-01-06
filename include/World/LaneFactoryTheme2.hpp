#pragma once
#include <LaneFactory.hpp>

class LaneFactoryTheme2 : public LaneFactory {
private:

    void templateStartLane(int num);
    void templateFinishTheme(int num);
    void templateGround(int num);
    void templateRoad(int num);
    void templateAnimalRoad(int num);
    void templateRiver(int num);
    void templateRailway(int num);

    void templateLevel1();
    void templateLevel2();
    void templateLevel3();
    void templateLevel4();
    void templateLevel5();

public:
    LaneFactoryTheme2(TextureHolder* textureHolder, sf::Vector2f startPos, int level);
};