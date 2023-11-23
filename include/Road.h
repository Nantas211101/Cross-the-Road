#pragma once

#include "Lane.h"
#include "Entity.h"
#include "DataTable.h"
#include "SFML/System/Vector2.hpp"
#include "TextureHolder.h"
#include "Animal.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>

class Road : public Lane {
    public:
        Road(sf::Vector2f spawnPos, const TextureHolder& texture, bool checkLine);
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        void loadTexture();
        void generateAnimal();
    private:
        std::vector<Animal*> animals;
        const int numOfAnimal = 10;
        int lastAnimalIndex;
        int firstAnimalIndex;
        sf::Vector2f startPos;
       
        sf::Sprite sprite;
        TextureHolder textureHolder;
};