#pragma once

#include <SceneNode.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/Graphics.hpp>
#include <ctime>
#include <math.h>

class Lane : public SceneNode {
    public:
        enum Type {
            Road,
            River,
            Ground,
            FinishLane,
            TypeCount
        };

    public:
        Lane(TextureHolder* textureHolder, sf::Vector2f spawnPos);
        bool isReverse();
        static const int distanceBetweenLane = 100;
        static const int distanceBetweenTile = 100;
        static const int widthOfLane = 2800;
        virtual unsigned int getCategory() const;
        
    private:
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt) = 0;
        virtual void buildLane() = 0;
        virtual sf::FloatRect getBoundingRect() const;

    private:
        bool reverse;

    protected:
        sf::Vector2f startPos;
        sf::Sprite sprite;
        TextureHolder* textureHolder;
        Animation animation;
};