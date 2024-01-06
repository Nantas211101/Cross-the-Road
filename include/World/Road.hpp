#pragma once

#include <Lane.hpp>
#include <Entity.hpp>
#include <DataTable.hpp>
#include <Animal.hpp>
#include <Vehicle.hpp>
#include <Traffic.hpp>

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class Road : public Lane {
    public:
        Road(TextureHolder* textureHolder, sf::Vector2f spawnPos, int difficulty);
        virtual void setLaneVelocity() = 0;
    private:
        virtual void updateCurrent(sf::Time dt) = 0;

    protected:
        int lastObjectIndex;
        int firstObjectIndex;
        const int numOfObject = 10;
};

namespace {
    const std::vector<AnimalData> TableAnimal = initializeAnimalData();
}
namespace {
    const std::vector<VehicleData> TableVehicle = initializeVehicleData();
}