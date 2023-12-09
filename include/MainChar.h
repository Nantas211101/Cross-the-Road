#pragma once

#include "World/Entity.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "utility.h"
#include "Animation.h"
#include "TextNode.h"
#include <string>

class MainChar : public Entity{
public:
    enum Type{
        Player1,
        Chicken,
        Penguin,
        Sheep,
        Mallard,
        none,
    };

private:
    Type                numToID(int num);
    int                 IDToNum(Type type);
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect       getBoundingRect() const;
    void                updateTexts();
    void                updateCurrent(sf::Time dt);


public:
    explicit            MainChar(Type type, const TextureHolder& textures, const FontHolder& fonts);
    void                changeTexture(bool isIncrease, const TextureHolder& textures);  
    void                setTexture(Textures::ID id, const TextureHolder& textures);

    virtual unsigned int getCategory() const;

    Type                getTextureType();
    Textures::ID        getTextureID();

    int					getHitpoints() const;
    void				heal(int points);
    void				damage(int points);
    void				destroy();
    virtual bool		isDestroyed() const;
    
    void                goUp();
    void                goDown();
    void                goLeft();
    void                goRight();
    void                stop();
    
private: 
    Type mType;
    sf::Sprite mSprite;
    TextNode* mHealthDisplay;
    int mHP;

    const int movingVelocity = 200;
    Animation upAnimation;
    Animation downAnimation;
    Animation leftAnimation;
    Animation rightAnimation;

    bool isGoingUp;
    bool isGoingDown;
    bool isGoingLeft;
    bool isGoingRight;
    // Animation deathAnimation;
    // Animation healingAnimation;
    // Animation takingDamageAnimation;
};