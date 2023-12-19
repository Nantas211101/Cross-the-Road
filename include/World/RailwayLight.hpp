#pragma once
#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics.hpp>

class RailwayLight : public Entity {
     public:
        RailwayLight(const TextureHolder& Texture);
        int getRailwayLightState();
        void setTimeCount();
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        
    private:
        int sta;
        sf::Sprite sprite;
        sf::FloatRect bounds;
        const float redTime = 4.0f;
        const float greenTime = 6.0f;
        sf::Time timeCount;
};