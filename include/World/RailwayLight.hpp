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
        const float redTime = 0.5f;
        const float greenTime = 0.5f;
};