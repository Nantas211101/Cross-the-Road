#pragma once

#include <Lane.hpp>
#include <Train.hpp>
#include <RailwayLight.hpp>
#include <DataTable.hpp>

#include <random>
#include <SFML/Graphics.hpp>

class Railway : public Lane {
    public:
        enum Type{
            Train1,
            SnowTrain,
            WoodTrain,
            LavaTrain,
            SantaTrain,
            TypeCount
        };
        Railway(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type type);
        Type getType(){
            return type;
        }
    private:
        void buildLane();
        void buildLight();
        void updateCurrent(sf::Time dt);

    private:
        Type type;
        Train* train;
        RailwayLight* railwayLight;
};