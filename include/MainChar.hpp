#pragma once

#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <utility.hpp>
#include <Animation.hpp>
#include <TextNode.hpp>
#include <Lane.hpp>
#include <DataTable.hpp>

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
        TypeCount
    };


private:
    Type                numToID(int num);
    int                 IDToNum(Type type);
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect       getBoundingRect() const;
    void                updateTexts();
    void                updateCurrent(sf::Time dt);

    void                makeStop();

public:
    explicit            MainChar(Type type, const TextureHolder& textures, const FontHolder& fonts, int curLane, const std::vector<Lane*>& lanes);
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
    void                stopMoving();
    bool                isStanding();

    void                setInLane(const std::vector<Lane*>& lanes);
    void                resetState();
    int                 getCurLane();
    void                backTolastLane();
    sf::Vector2f        getLastPos();
    void                alignChar();

private:
    enum State {
        Up,
        Down,
        Right,
        Left,
        Standing,
    };
    Type mType;
    sf::Sprite mSprite;
    TextNode* mHealthDisplay;
    int mHP;

    const int movingVelocity = 350;
    Animation upAnimation;
    Animation downAnimation;
    Animation leftAnimation;
    Animation rightAnimation;

    State state;
	sf::Vector2f lastPosSinceMoving;
    int curLane;
    int prevLane;
    // Animation deathAnimation;
    // Animation healingAnimation;
    // Animation takingDamageAnimation;
};