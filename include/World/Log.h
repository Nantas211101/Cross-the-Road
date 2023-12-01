#pragma once

#include "Entity.h"
#include "../DataTable.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Log : public Entity {
    public:
        enum Type{
            Log1,
            Log2,
            Log3,
            Crocodile,
            TypeCount
        };

    public:
        Log(Type type, const TextureHolder& Texture);
        virtual sf::FloatRect getBoundingRect() const;
        sf::FloatRect* getDangerBound() const;
        Type getType();

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
        Type type;
        sf::Sprite sprite;
};