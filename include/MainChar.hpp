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
        Sheep,
        Mallard,
        TypeCount,
    };

    static Textures::ID toTextureID(MainChar::Type type);

private:
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect       getBoundingRect() const;
    void                updateTexts();
    void                updateCurrent(sf::Time dt);

    void                makeStop();
    void                setInLane(const std::vector<Lane*>& lanes);
    void                setInGrid();

    void                setOwnerShip(bool flag);

public:
    explicit            MainChar(Type type, const TextureHolder& textures, const FontHolder& fonts, int curLane, int curGrid, const std::vector<Lane*>& lanes);
    explicit            MainChar(Type type, const TextureHolder& textures, sf::Vector2f pos);
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

    void                resetState();
    int                 getCurLane();
    void                fixInPos(const std::vector<Lane*>& lanes);
    void                backTolastPos(const std::vector<Lane*>& lanes);
    sf::Vector2f        getLastPos();
    
    Type getMainCharType();
    int getThisMaskID();
    void setOwnerFlag(bool flag);

    void setCenterOriginMainChar();

    // Ham de fix bug
    void whatIsCurrentState();


private:
    enum State {
        Up,
        Down,
        Right,
        Left,
        Standing,
        Rest
    };
    Type mType;
    sf::Sprite mSprite;
    bool ownerFlag;

    TextNode* mHealthDisplay;
    int mHP;

    const int movingVelocity = 350;
    Animation upAnimation;
    Animation downAnimation;
    Animation leftAnimation;
    Animation rightAnimation;
    Animation restAnimation;
    Animation deathAnimation;

    State state;
	sf::Vector2f lastPosSinceMoving;
    int curLane;
    int prevLane;
    int curGrid;
    int prevGrid;
    // Animation healingAnimation;
    // Animation takingDamageAnimation;
};

int convertToMaskID(MainChar::Type type);
MainChar::Type changeTexture(MainChar::Type type, bool isLeft);  