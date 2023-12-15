#pragma once

#include <Lane.hpp>
#include <Train.hpp>
#include <RailwayLight.hpp>
#include <DataTable.hpp>

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