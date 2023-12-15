#pragma once

#include <Lane.hpp>
#include <Entity.hpp>
#include <DataTable.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <Obstacle.hpp>
#include <Decorator.hpp>

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