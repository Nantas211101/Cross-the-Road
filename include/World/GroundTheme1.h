#pragma once
#include <Ground.h>

class GroundTheme1 : public Ground {
    public:
        enum Type{
            Grass,
            Soil,
            TypeCount
        };
        GroundTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround);
    
    private:
        void buildLane();
        void updateCurrent(sf::Time dt);
    
    private:
        Type typeGround;
        std::vector<Obstacle*> obstacles;
        std::vector<Decorator*> decorators;
};