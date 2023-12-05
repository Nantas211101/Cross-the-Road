#pragma once

#include "Lane.h"
#include "Entity.h"
#include "../DataTable.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"
#include "Animal.h"
#include "Vehicle.h"
#include "Traffic.h"

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class RailWay : public Lane {
    public:
        RailWay(sf::Vector2f spawnPos, bool checkLine);
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        void loadTexture();
        void generateTrain();
        void buildTraffic();
    private:
        std::vector<Vehicle*> vehicles;
        const int numOfObject = 5;
        int lastObjectIndex;
        int firstObjectIndex;
        sf::Vector2f startPos;
        Traffic* traffic;
        sf::Sprite sprite;
        TextureHolder textureHolder;
        bool hasTraffic;
        Vehicle::Type kind;
};