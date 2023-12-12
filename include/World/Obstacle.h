#pragma once

#include "Entity.h"
#include "../DataTable.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"

#include <SFML/Graphics.hpp>

class Obstacle : public Entity {
    public:
        enum Type{
            Tree1,
            Tree2,
            Tree3,
            Rock1,
            Rock2,
            Ruin1,
            Ruin2,
            Volcano,
            TypeCount
    };

    public:
        Obstacle(Type type, const TextureHolder& Texture);
        virtual sf::FloatRect getBoundingRect() const;
        sf::FloatRect* getDangerBound() const;
        Type getType();
        virtual unsigned int getCategory() const;
        int getDamage();
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
        Type type;
        sf::Sprite sprite;
};