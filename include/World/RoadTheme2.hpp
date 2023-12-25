#pragma once 
#include <Road.hpp>

class RoadTheme2 : public Road {
    public:
        enum Type{
            AnimalRoad,
            VehicleRoad,
            TypeCount
        };
        RoadTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos, bool checkLine, Type typeRoad, int difficulty);
        void setLaneVelocity();
    private:
        void buildLane();
        void generateAnimal();
        void generateVehicle();
        void buildTraffic();
        void updateCurrent(sf::Time dt);

    private:
        bool checkLine;
        bool hasTraffic;
        Type typeRoad;
        std::vector<Animal*> animals;
        std::vector<Vehicle*> vehicles;
        Traffic* traffic;
};