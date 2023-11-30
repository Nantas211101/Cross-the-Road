#pragma once

#include "World/Entity.h"
#include "World/TextureHolder.h"
#include "utility.h"

class MainChar : public Entity{
public:
    enum Type{
        Chicken,
        Penguin,
        Sheep,
        Mallard,
        none,
    };

private:
    Type numToID(int num);
    int IDToNum(Type type);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    explicit MainChar(Type type, const TextureHolder& textures);
    void changeTexture(bool isIncrease, const TextureHolder& textures);  
    void setTexture(Textures::ID id, const TextureHolder& textures);

    virtual unsigned int getCategory() const;

    Type getTextureType();
    Textures::ID getTextureID();

    sf::FloatRect getBoundingRect() const;

private: 
    Type mType;
    sf::Sprite mSprite;
};