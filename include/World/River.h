#pragma once

#include "Lane.h"
#include "Log.h"
#include "../DataTable.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

class River : public Lane {
    public:
        River(TextureHolder* textureHolder, sf::Vector2f spawnPos);

    private:
        void buildLane();
   
        void updateCurrent(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual unsigned int getCategory() const;
        virtual sf::FloatRect getBoundingRect() const;

    private:
        std::vector<Log*> riverLog;
        const int numOfLog = 10;
        int lastLogIndex;
        int firstLogIndex;
        sf::Vector2f startPos;
        
        sf::Sprite sprite;
        TextureHolder* textureHolder;
};