#pragma once

#include "Entity.h"
#include "../DataTable.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Train : public Entity {
    public:
        enum Type{
            Train1,
            Train2,
            Train3,
            TypeCount
        };

    public:
        Train(Type type, const TextureHolder& Texture);
        virtual sf::FloatRect getBoundingRect() const;
        Type getType();

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
        Type type;
        sf::Sprite sprite;
};