#pragma once

#include <Lane.hpp>
#include <DataTable.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <Decorator.hpp>

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class FinishLane: public Lane{
    public:
        enum Type{
            Level1,
            Level2,
            Level3,
            Theme1,
            Theme2,
            Theme3,
            TypeCount
        };
        FinishLane(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeFinishLane);

    private:
        void buildLane();
        void updateCurrent(sf::Time dt);

    private:
        Type typeFinishLane;
        std::vector<Decorator*> decorators;
};