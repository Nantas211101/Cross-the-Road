#pragma once
#include <River.hpp>

class RiverTheme3 : public River {
    public:
        RiverTheme3(TextureHolder* textureHolder, sf::Vector2f spawnPos);
        void playLocalSound(CommandQueue& commands);

    private:
        void buildLane();
        void updateCurrent(sf::Time dt);

    private:
        std::vector<Log*> riverLog;
};