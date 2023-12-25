#include <LaneFactory.hpp>

LaneFactory::LaneFactory(TextureHolder* textureHolder, sf::Vector2f startPos, int level)
: lanes()
, textureHolder(textureHolder)
, startPos(startPos)
, level(level)
{}

void LaneFactory::templateFinishLevel(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane * 3;
        lanes.push_back(std::move(lane));
    }
}