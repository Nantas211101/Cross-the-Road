#pragma once

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class MainChar : public Entity{
public:
    enum Type{
        none,
        Chicken,
        Penguin,
        Sheep,
        Mallard,
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

private:

private: 
    Type mType;
    sf::Sprite mSprite;
};