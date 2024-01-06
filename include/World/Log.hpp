#pragma once

#include <Entity.hpp>
#include <DataTable.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics.hpp>

class Log : public Entity {
    public:
        enum Type{
            Log1,
            Log2,
            Log3,
            SnowLog1,
            SnowLog2,
            Crocodile,
            TypeCount
        };

    public:
        Log(Type type, const TextureHolder& Texture);
        virtual unsigned int getCategory() const;
        virtual sf::FloatRect getBoundingRect() const;
        Type getType();

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
        Type type;
        sf::Sprite sprite;
};