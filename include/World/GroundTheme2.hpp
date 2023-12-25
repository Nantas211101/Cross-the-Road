#pragma once
#include <Ground.hpp>

class GroundTheme2 : public Ground {
    public:
        enum Type{
            Snow,
            Soil,
            TypeCount
        };
        GroundTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround,bool isStart, int difficulty);
    
    private:
        void buildLane();
        void updateCurrent(sf::Time dt);
    
    private:
        Type typeGround;
        bool isStartLane;
        std::vector<Obstacle*> obstacles;
        std::vector<Decorator*> decorators;
};