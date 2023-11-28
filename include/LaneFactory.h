#pragma once
#include "Lane.h"
#include "River.h"
#include "Grass.h"
#include "Road.h"
#include "TextureHolder.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class LaneFactory {
private:
    std::vector<std::unique_ptr<Lane>> lanes;
    sf::Vector2f startPos;

    void templateGrass(int num);
    void templateRoad(int num);
    void templateRiver(int num);

    void templateLane1();
    void templateLane2();
    void templateLane3();
    void templateLane4();
    void templateLane5();

public:
    LaneFactory(sf::Vector2f startPos);
    
    std::vector<std::unique_ptr<Lane>> randomTemplateLane();
};