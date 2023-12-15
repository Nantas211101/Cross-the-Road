#pragma once
#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics.hpp>

class RailwayLight : public Entity {
     public:
        RailwayLight(const TextureHolder& Texture);
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