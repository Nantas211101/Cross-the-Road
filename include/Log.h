#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "DataTable.h"
#include "TextureHolder.h"
#include <iostream>

class Log : public Entity {
    public:
        enum Type{
            Log1,
            Crocodile,
            TypeCount
        };

    public:
        Log(Type type, const TextureHolder& Texture);
        virtual sf::FloatRect getBoundingRect() const;
        sf::FloatRect* getDangerBound() const;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
        Type type;
        sf::Sprite sprite;
};