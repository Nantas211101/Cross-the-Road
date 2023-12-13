#pragma once 
#include <Road.h>

class RoadTheme2 : public Road {
    public:
        RoadTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos, bool checkLine);

    private:
        void buildLane();
        void generateAnimal();
        void generateVehicle();
        
        void updateCurrent(sf::Time dt);

    private:
        bool checkLine;
        int typeRoad;
        std::vector<Animal*> animals;
        std::vector<Vehicle*> vehicles;
};