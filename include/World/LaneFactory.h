#pragma once
#include "Lane.h"
#include "River.h"
#include "Ground.h"
#include "Road.h"
#include "Railway.h"
#include "RoadTheme1.h"
#include "RoadTheme2.h"
#include "GroundTheme1.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class LaneFactory {
private:
    std::vector<std::unique_ptr<Lane>> lanes;
    sf::Vector2f startPos;
    TextureHolder* textureHolder;

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
    LaneFactory(TextureHolder* textureHolder, sf::Vector2f startPos);
    
    std::vector<std::unique_ptr<Lane>> randomTemplateLane();
};