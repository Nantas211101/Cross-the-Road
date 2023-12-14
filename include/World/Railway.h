#pragma once

#include <Lane.h>
#include <Train.h>
#include <RailwayLight.h>
#include <DataTable.h>

#include <random>
#include <SFML/Graphics.hpp>

class Railway : public Lane {
    public:
        Railway(TextureHolder* textureHolder, sf::Vector2f spawnPos);
    
    private:
        void buildLane();
        void buildLight();
        void updateCurrent(sf::Time dt);

    private:
        Train* train;
        RailwayLight* railwayLight;
};