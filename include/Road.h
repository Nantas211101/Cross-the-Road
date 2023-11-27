#pragma once

#include "Lane.h"
#include "Entity.h"
#include "DataTable.h"
#include "SFML/System/Vector2.hpp"
#include "TextureHolder.h"
#include "Animal.h"
#include "Vehicle.h"
#include <vector>
#include "Traffic.h"
#include <SFML/Graphics.hpp>

class Road : public Lane {
    public:
        Road(sf::Vector2f spawnPos, const TextureHolder& texture);

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        void loadTexture();
        void generateAnimal();
        void generateVehicle();
        void buildTraffic();
    private:
        std::vector<Animal*> animals;
        std::vector<Vehicle*> vehicles;
        const int numOfObject = 10;
        int lastObjectIndex;
        int firstObjectIndex;
        sf::Vector2f startPos;
        Traffic* traffic;
        sf::Sprite sprite;
        TextureHolder textureHolder;
        bool hasTraffic;
        Vehicle::Type kind;
};