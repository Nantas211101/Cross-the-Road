#pragma once

#include "Entity.h"
#include "DataTable.h"
#include "TextureHolder.h"
#include "Lane.h"
#include "SpriteNode.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Grass : public Lane {
    public:
        Grass(const TextureHolder& texture);
        Grass(const TextureHolder& texture, const sf::IntRect& textureRect);
    
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
   
    private:
        sf::Sprite sprite;
        // std::vector<Log> riverLog;
};