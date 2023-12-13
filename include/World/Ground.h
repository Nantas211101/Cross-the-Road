#pragma once

#include <Lane.h>
#include <DataTable.h>
#include <Obstacle.h>

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