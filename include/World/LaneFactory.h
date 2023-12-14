#pragma once
#include <Railway.h>
#include <RoadTheme1.h>
#include <RoadTheme2.h>
#include <RiverTheme1.h>
#include <RiverTheme2.h>
#include <GroundTheme1.h>
#include <GroundTheme2.h>
#include <FinishLane.h>

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class LaneFactory {
protected:
    std::vector<std::unique_ptr<Lane>> lanes;
    sf::Vector2f startPos;
    TextureHolder* textureHolder;
    int theme;
    
public:
    LaneFactory(TextureHolder* textureHolder, sf::Vector2f startPos, int theme);
    virtual std::vector<std::unique_ptr<Lane>> randomTemplateLane() = 0;
};