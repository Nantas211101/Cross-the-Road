#pragma once

#include "Entity.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"

#include <SFML/Graphics.hpp>

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