#pragma once

#include <Lane.h>
#include <Entity.h>
#include <DataTable.h>
#include <ResourceIdentifiers.h>
#include <ResourceHolder.h>
#include <Obstacle.h>
#include <Decorator.h>

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class Ground : public Lane {
    public:
        Ground(TextureHolder* textureHolder, sf::Vector2f spawnPos);

    private:
        virtual void updateCurrent(sf::Time dt) = 0;
};

namespace {
    const std::vector<ObstacleData> TableObstacle = initializeObstacleData();
}