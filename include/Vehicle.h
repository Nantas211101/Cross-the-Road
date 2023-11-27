#pragma once
#include <vector>
#include "Entity.h"
#include "DataTable.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics.hpp>

class Vehicle:public Entity{
 public:
    enum Type{
        Truck,
        Car,
        TypeCount
    };
 public:
    Vehicle(Type type, const TextureHolder& texture);
    Type getType();
    
 private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
    void updateCurrent(sf::Time dt);
 private:
    Type type;
    sf::Sprite sprite;
};