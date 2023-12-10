#pragma once
#include "Entity.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"

#include <SFML/Graphics.hpp>

class RailwayLight: public Entity{
     public:
        RailwayLight( const TextureHolder& Texture);
        // virtual sf::FloatRect getBoundingRect() const;
        // sf::FloatRect* getDangerBound() const;
        int getRailwayLightState();
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        
    private:
        int sta;
        sf::Time timeCount;
        sf::Sprite sprite;
        sf::FloatRect bounds;
        const float redTime = 1.0f;
        const float greenTime = 6.0f;
};