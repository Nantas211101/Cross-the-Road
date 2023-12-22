#pragma once

#include <Entity.hpp>
#include <DataTable.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <SceneNode.hpp>

#include <SFML/Graphics.hpp>

class Decorator : public Entity {
    public:
        enum Type{
            DecoRock1,
            DecoRock2,
            DecoStone,
            Skullcap1,
            Skullcap2,
            DecoTree1,
            DecoTree2,
            DecoFlower1,
            DecoFlower2,
            DecoIce1,
            DecoSnow1,
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