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