#pragma once
#include <River.hpp>

class RiverTheme1 : public River {
    public:
        RiverTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos);

    private:
        void buildLane();
        void updateCurrent(sf::Time dt);
        sf::FloatRect getBoundingRect() const;

    private:
        std::vector<Log*> riverLog;
};