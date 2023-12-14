#pragma once
#include <Entity.h>
#include <ResourceIdentifiers.h>
#include <ResourceHolder.h>

#include <SFML/Graphics.hpp>

class Traffic: public Entity{
     public:
        Traffic(const TextureHolder& Texture);
        int getTrafficState();

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        
    private:
        int sta;
        sf::Time timeCount;
        sf::Sprite sprite;
        sf::FloatRect bounds;
        const float redTime = 1.0f;
        const float yellowTime = 1.0f;
        const float greenTime = 3.0f;
};