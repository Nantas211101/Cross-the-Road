#pragma once

#include "Lane.h"
#include "Log.h"
#include "SpriteNode.h"
#include <vector>
#include <SFML/Graphics.hpp>

class River : public Lane {
    public:
        River(const TextureHolder& texture);
        River(const TextureHolder& texture, const sf::IntRect& textureRect);
    
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
   
    private:
        sf::Sprite sprite;
        std::vector<Log> riverLog;
};