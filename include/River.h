#pragma once

#include "Lane.h"
#include "Log.h"
#include "DataTable.h"
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

class River : public Lane {
    public:
        River(sf::Vector2f spawnPos, const TextureHolder& texture);
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        void loadTexture();
        void buildLog();
   
    private:
        std::vector<Log*> riverLog;
        const int numOfLog = 10;
        int lastLogIndex;
        int firstLogIndex;
        sf::Vector2f startPos;
        
        sf::Sprite sprite;
        TextureHolder textureHolder;
};