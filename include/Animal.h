#pragma once
#include <vector>
#include "Entity.h"
#include "DataTable.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Animal:public Entity{
 public:
    enum Type{
        Elephant,
        Rhinoceros,

        Small_Dragon,
        Green_Dragon,
        Red_Dragon,
        Blue_Twin_Head_Dragon,
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
    Animation sprite;
};