#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "DataTable.h"
#include "TextureHolder.h"

class Log : public Entity {
    public:
        enum Type{
            Log1,
            Crocodile,
            TypeCount
        };

    public:
        Log(Type type, const TextureHolder& Texture);

    private:
        Type type;
        sf::Sprite sprite;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
};