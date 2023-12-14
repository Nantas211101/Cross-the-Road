#pragma once

#include <Lane.h>
#include <DataTable.h>
#include <ResourceIdentifiers.h>
#include <ResourceHolder.h>
#include <Decorator.h>

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