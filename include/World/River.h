#pragma once

#include "Lane.h"
#include "Entity.h"
#include "../DataTable.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"
#include "Log.h"

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class River : public Lane {
    public:
        River(TextureHolder* textureHolder, sf::Vector2f spawnPos);

    private:
        virtual void updateCurrent(sf::Time dt) = 0;
};

namespace {
    const std::vector<LogData> TableLog = initializeLogData();
}