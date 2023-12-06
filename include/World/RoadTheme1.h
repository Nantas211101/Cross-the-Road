#pragma once 
#include "Road.h"

class RoadTheme1 : public Road {
    public:
        RoadTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos, bool checkLine);
        void generateAnimal();
        void generateVehicle();
        void buildTraffic();

    private:
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);

    private:
        bool checkLine;
        sf::Sprite sprite;
        bool hasTraffic;
        std::vector<Animal*> animals;
        std::vector<Vehicle*> vehicles;
        Traffic* traffic;
};