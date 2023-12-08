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

class Road : public Lane {
    public:
        Road(TextureHolder* textureHolder, sf::Vector2f spawnPos);

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