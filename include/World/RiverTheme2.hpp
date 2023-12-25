#pragma once
#include <River.hpp>

class RiverTheme2 : public River {
    public:
        RiverTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos, int difficulty);
        void setLaneVelocity();
    private:
        void buildLane();
        void updateCurrent(sf::Time dt);

    private:
        std::vector<Log*> riverLog;
};