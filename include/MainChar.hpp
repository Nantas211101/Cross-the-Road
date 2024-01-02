#pragma once

#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <Utility.hpp>
#include <Animation.hpp>
#include <TextNode.hpp>
#include <Lane.hpp>
#include <DataTable.hpp>

#include <string>

class Player1;
class Player2;
class Player3;

class MainChar : public Entity{
friend Player1;
friend Player2;
friend Player3;
public:
    enum Type{
        Player1,
        Player2,
        Player3,
        Player4,
        Player5,
        TypeCount,
    };

    static Textures::ID toTextureID(MainChar::Type type);

private:
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect       getBoundingRect() const;
    virtual void        updateCurrent(sf::Time dt);

    void                makeStop();
    void                setInLane();

    void                setOwnerShip(bool flag);

public:
    explicit            MainChar(Type type, const TextureHolder& textures, int curLane, std::vector<Lane*>& lanes);
    explicit            MainChar(Type type, const TextureHolder& textures, sf::Vector2f pos);
    void                setTexture(Textures::ID id, const TextureHolder& textures);

    virtual unsigned int getCategory() const;

    Type                getTextureType();
    Textures::ID        getTextureID();

    int					getHitpoints() const;
    int                 getMaxHP() const;
    int                 getManaPoints() const;
    int                 getMaxMP() const;

    void                addMana(int points);
    void				heal(int points);
    void				damage(int points);
    bool	        	isDead() const;
    
    void                goUp();
    void                goDown();
    void                goLeft();
    void                goRight();
    void                stopMoving();
    bool                isStanding();
    virtual void        useAbility();
    bool                canUseAbility();

    void                resetState();
    int                 getCurLane();
    void                backTolastPos();
    
    Type getMainCharType();
    int getThisMaskID();
    void setOwnerFlag(bool flag);

    void setCenterOriginMainChar();


private:
    enum State {
        Down,
        Left,
        Right,
        Up,
        Standing,
        Rest
    };
    Type mType;
    sf::Sprite mSprite;
    Animation upAnimation;
    Animation downAnimation;
    Animation leftAnimation;
    Animation rightAnimation;
    Animation restAnimation;
    // Animation deathAnimation;
    bool ownerFlag;

    State state;
    std::vector<Lane*>* lanes;
	sf::Vector2f lastPosSinceMoving;
    int curLane;

    int mHP;
    const int maxHP;
    int mMP;
    const int maxMP;
    int movingVelocity;
    sf::Clock timeSinceLastDamage;
    const sf::Time damageGap = sf::seconds(1);
};

int convertToMaskID(MainChar::Type type);
MainChar::Type changeTexture(MainChar::Type type, bool isLeft);  