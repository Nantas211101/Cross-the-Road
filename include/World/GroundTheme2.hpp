#pragma once
#include <Ground.hpp>

class GroundTheme2 : public Ground {
    public:
        enum Type{
            Lava,
            Soil,
            TypeCount
        };
        GroundTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround,bool isStart);
    
    private:
        void buildLane();
        void updateCurrent(sf::Time dt);
    
    private:
        Type typeGround;
        bool isStartLane;
        std::vector<Obstacle*> obstacles;
};