#pragma once

#include "Entity.h"
#include "../DataTable.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"
#include "Lane.h"
#include "Obstacle.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Ground : public Lane {
    public:
        enum Type{
            Grass,
            Soil,
            TypeCount
        };
        Ground(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeGround);
    
    private:
        void buildLane();
        void updateCurrent(sf::Time dt);
    
    private:
        Type typeGround;
        std::vector<Obstacle*> obstacles;
};