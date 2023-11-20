#pragma once
#include <vector>
#include "Entity.h"
#include "DataTable.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics.hpp>

class Animal:public Entity{
 public:
    enum Type{
        Elephant,
        Bird, 
        Rhinoceros,
        //Buffalo,
        //Hippo,
       
        TypeCount
    };
 public:
    Animal(Type type, const TextureHolder& texture);
    Type getType();
    
 private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
    void updateCurrent(sf::Time dt);
 private:
    Type type;
    sf::Sprite sprite;
};