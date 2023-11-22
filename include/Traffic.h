#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

#include "TextureHolder.h"

class Traffic: public Entity{
     public:
        Traffic( const TextureHolder& Texture,int status);
        // virtual sf::FloatRect getBoundingRect() const;
        // sf::FloatRect* getDangerBound() const;
        int getTrafficState();
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        
    private:
        int sta;
        sf::Time timeCount;
        sf::Sprite sprite;
        sf::FloatRect bounds;
        const float redTime = 5.0f;
        const float yellowTime = 2.0f;
        const float greenTime = 3.0f;
};