#include <LaneFactory.hpp>

LaneFactory::LaneFactory(TextureHolder* textureHolder, sf::Vector2f startPos, int theme)
: lanes()
, textureHolder(textureHolder)
, startPos(startPos)
, theme(theme)
{}

void LaneFactory::templateFinishLevel(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, FinishLane::Level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane * 3;
        lanes.push_back(std::move(lane));
    }
}