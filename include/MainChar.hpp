#pragma once

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
class MainChar : public Entity{
public:
    enum Type{
        Chicken,
        Penguin,
        Sheep,
        Mallard,
        TypeCount,
    };

    static Textures::ID toTextureID(MainChar::Type type);

private:
    Type numToID(int num);
    int IDToNum(Type type);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    explicit MainChar(Type type, const TextureHolder& textures);
    void changeTexture(bool isIncrease, const TextureHolder& textures);  
    void setTexture(Textures::ID id, const TextureHolder& textures);

    virtual unsigned int getCategory() const;

    Type getMainCharType();
    Textures::ID getTextureID();

    int getThisMaskID();

    void setOwnerFlag(bool flag);

private: 
    Type mType;
    sf::Sprite mSprite;
    bool ownerFlag;
};

int convertToMaskID(MainChar::Type type);