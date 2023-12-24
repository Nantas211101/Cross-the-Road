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
            Level,
            Theme1,
            Theme2,
            Theme3,
            TypeCount
        };
        FinishLane(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeFinishLane);
        int getNum();
    private:
        void buildLane();
        void updateCurrent(sf::Time dt);

    private:
        Type typeFinishLane;
        int num;
        std::vector<Decorator*> decorators;
};