#pragma once
#include "Ground.h"

class GroundTheme2 : public Ground {
    public:
        enum Type{
            Lava,
            Soil,
            TypeCount
        };
        GroundTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround);
    
    private:
        void buildLane();
        void updateCurrent(sf::Time dt);
    
    private:
        Type typeGround;
        std::vector<Obstacle*> obstacles;
};