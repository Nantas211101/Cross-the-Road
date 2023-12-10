#pragma once

#include "../SceneNode.h"
#include "../ResourceHolder.h"
#include "../ResourceIdentifiers.h"
#include <SFML/Graphics.hpp>
#include <ctime>

class Lane : public SceneNode {
    public:
        enum Type {
            Road,
            River,
            Ground,
            TypeCount
        };

    public:
        Lane(TextureHolder* textureHolder, sf::Vector2f spawnPos);
        bool isReverse();
        static const int distanceBetweenLane = 100;
        static const int distanceBetweenTile = 150;
        
    private:
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt) = 0;
        virtual void buildLane() = 0;

    private:
        bool reverse;

    protected:
        sf::Vector2f startPos;
        sf::Sprite sprite;
        TextureHolder* textureHolder;
};