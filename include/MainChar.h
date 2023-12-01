#pragma once

#include "World/Entity.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "utility.h"
#include "Animation.h"

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
    sf::FloatRect getBoundingRect() const;

public:
    explicit MainChar(Type type, const TextureHolder& textures);
    void changeTexture(bool isIncrease, const TextureHolder& textures);  
    void setTexture(Textures::ID id, const TextureHolder& textures);

    virtual unsigned int getCategory() const;

    Type getTextureType();
    Textures::ID getTextureID();

    int					getHitpoints() const;
	void				heal(int points);
	void				damage(int points);
	void				destroy();
	virtual bool		isDestroyed() const;

private: 
    Type mType;
    sf::Sprite mSprite;
    int mHP;
    // Animation MovingAnimation;
    // Animation deathAnimation;
    // Animation healingAnimation;
    // Animation takingDamageAnimation;
};