#pragma once

#include <Entity.hpp>
#include <DataTable.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics.hpp>

class Obstacle : public Entity {
    public:
        enum Type{
            Tree1,
            Tree2,
            Tree3,
            SnowTree,
            SnowTree1,
            Rock1,
            Rock2,
            Ruin1,
            Ruin2,
            Volcano,
            Fire,
            SnowMan,
            TypeCount
    };

    public:
        Obstacle(Type type, const TextureHolder& Texture);
        virtual sf::FloatRect getBoundingRect() const;
        Type getType();
        virtual unsigned int getCategory() const;
        int getDamage();

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
        Type type;
        Animation sprite;
};