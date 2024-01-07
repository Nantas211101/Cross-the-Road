#pragma once

#include "SFML/System/Vector2.hpp"
#include <SceneNode.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <random>

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
        Lane(TextureHolder* textureHolder, sf::Vector2f spawnPos, int difficulty);
        Lane(TextureHolder* textureHolder, sf::Vector2f spawnPos, int difficulty, bool reverse);
        bool isReverse();
        virtual void setLaneVelocity() = 0;
        virtual unsigned int getCategory() const;

        static const int distanceBetweenLane = 100;
        static const int distanceBetweenTile = 100;
        static const int widthOfLane = 2800;
        static const int maxLevel = 5;
        static const int distanceBetweenStartPos = 150;
        static const int minCoefficientRandPos = -15;
        static const int maxCoefficientRandPos = -1;
        
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
        int difficulty;
        sf::Vector2f transformVelocity(sf::Vector2f v);
};