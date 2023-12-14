#pragma once
#include <River.h>

class RiverTheme1 : public River {
    public:
        RiverTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos);

    private:
        void buildLane();
        void updateCurrent(sf::Time dt);

    private:
        std::vector<Log*> riverLog;
};