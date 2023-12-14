#pragma once

#include <Entity.h>
#include <DataTable.h>
#include <ResourceIdentifiers.h>
#include <ResourceHolder.h>
#include <SceneNode.h>

#include <SFML/Graphics.hpp>

class Decorator : public Entity {
    public:
        enum Type{
            DecoRock1,
            DecoRock2,
            DecoTree1,
            DecoTree2,
            DecoFlower1,

            DecoFire1,
            DecoFire2,
            TypeCount
        };

    public:
        Decorator(Type type, const TextureHolder& texture);
        Type getType();

    private:
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
        Type type;
        sf::Sprite sprite;
};