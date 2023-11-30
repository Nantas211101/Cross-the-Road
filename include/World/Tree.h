#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

#include "TextureHolder.h"

class Tree : public Entity {
    

    public:
        Tree( const TextureHolder& Texture);
        virtual sf::FloatRect getBoundingRect() const;
        sf::FloatRect* getDangerBound() const;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
      
        sf::Sprite sprite;
};