#pragma once

#include "Lane.h"
#include "Train.h"
#include "../DataTable.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"
#include "../SceneNode.h"
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>


class Railway : public Lane {
    public:
        Railway(TextureHolder* textureHolder, sf::Vector2f spawnPos);
    
    private:
        void buildLane();
        
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);

    private:
        Train* train;
        sf::Vector2f startPos;
        sf::Sprite sprite;
        TextureHolder* textureHolder;
};