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
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);

        void generateTrain();
        void buildTraffic();
    private:
        std::vector<Vehicle*> vehicles;
        int lastObjectIndex;
        int firstObjectIndex;
        sf::Vector2f startPos;
        //Traffic* traffic;
        sf::Sprite sprite;
        TextureHolder* textureHolder;
        bool hasTraffic;
        Vehicle::Type kind;
};