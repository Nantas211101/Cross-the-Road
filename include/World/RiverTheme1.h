#pragma once
#include "River.h"

class RiverTheme1 : public River {
    public:
        RiverTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos);

    private:
        void buildLane();
   
        void updateCurrent(sf::Time dt);
        virtual unsigned int getCategory() const;
        virtual sf::FloatRect getBoundingRect() const;

    private:
        std::vector<Log*> riverLog;
        const int numOfLog = 10;
        int lastLogIndex;
        int firstLogIndex;
};