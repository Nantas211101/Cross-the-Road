#pragma once

#include "Lane.h"
#include "Log.h"
#include "DataTable.h"
#include "SpriteNode.h"
#include <vector>
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
        sf::Sprite sprite;
        std::vector<Log*> riverLog;
        sf::Time timeSinceLastLog;
        sf::Vector2f pos;
        TextureHolder textureHolder;
};