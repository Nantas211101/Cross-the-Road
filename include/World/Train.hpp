#pragma once

#include <Entity.hpp>
#include <DataTable.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics.hpp>

class Train : public Entity {
    public:
        enum Type{
            Train1,
            Train2,
            Train3,
            Train4,
            TypeCount
        };

    public:
        Train(Type type, const TextureHolder& Texture);
        virtual sf::FloatRect getBoundingRect() const;
        unsigned int getCategory() const;
        Type getType();

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
        Type type;
        sf::Sprite sprite;
};