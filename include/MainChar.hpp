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

class MainChar : public Entity{
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
    void                updateCurrent(sf::Time dt);

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
    void				heal(int points);
    void				damage(int points);
    bool	        	isDead() const;
    
    void                goUp();
    void                goDown();
    void                goLeft();
    void                goRight();
    void                stopMoving();
    bool                isStanding();

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
    Animation deathAnimation;
    bool ownerFlag;

    State state;
    std::vector<Lane*>* lanes;
	sf::Vector2f lastPosSinceMoving;
    int curLane;

    int mHP;
    int maxHP;
    int movingVelocity;

    // Animation healingAnimation;
    // Animation takingDamageAnimation;
};

int convertToMaskID(MainChar::Type type);
MainChar::Type changeTexture(MainChar::Type type, bool isLeft);  