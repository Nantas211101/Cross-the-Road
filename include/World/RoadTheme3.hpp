#pragma once 
#include <Road.hpp>

class RoadTheme3 : public Road {
    public:
        RoadTheme3(TextureHolder* textureHolder, sf::Vector2f spawnPos, bool checkLine, int difficulty);
        void setLaneVelocity();
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