#pragma once 
#include "Road.h"

class RoadTheme1 : public Road {
    public:
        RoadTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos, bool checkLine);

    private:
        void buildLane();
        void generateAnimal();
        void generateVehicle();
        void buildTraffic();
        
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);

    private:
        bool checkLine;
        bool hasTraffic;
        std::vector<Animal*> animals;
        std::vector<Vehicle*> vehicles;
        Traffic* traffic;
};