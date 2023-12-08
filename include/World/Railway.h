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
#include "RailwayLight.h"

class Railway : public Lane {
    public:
        Railway(TextureHolder* textureHolder, sf::Vector2f spawnPos);
    
    private:
        void buildLane();
        void buildLight();
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);

    private:
        Train* train;
        sf::Vector2f startPos;
        TextureHolder* textureHolder;
        RailwayLight* railwayLight;
};