#pragma once

#include <Lane.hpp>
#include <DataTable.hpp>
#include <Log.hpp>

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class River : public Lane {
    public:
        River(TextureHolder* textureHolder, sf::Vector2f spawnPos);

    private:
        virtual void updateCurrent(sf::Time dt) = 0;
        unsigned int getCategory() const;
        virtual sf::FloatRect getBoundingRect() const;

    protected:
        const int numOfLog = 10;
        int lastLogIndex;
        int firstLogIndex;
};

namespace {
    const std::vector<LogData> TableLog = initializeLogData();
}