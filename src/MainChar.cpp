#include <MainChar.hpp>
#include <TextureManipulate.hpp>
#include <BitMaskingManipulate.hpp>

namespace {
    const std::vector<CharData> Table = initializeCharData();
}

Textures::ID MainChar::toTextureID(MainChar::Type type)
{
    return Table[type].texture;
}

MainChar::Type toMainCharID(Textures::ID id)
{
    switch (id)
    {
    case Textures::Standing1:
    case Textures::Down1:
    case Textures::Left1:
    case Textures::Right1:
    case Textures::Up1:
        return MainChar::Player1;
    
    case Textures::Standing2:
    case Textures::Down2:
    case Textures::Left2:
    case Textures::Right2:
    case Textures::Up2:
        return MainChar::Player2;    

    case Textures::Standing3:
    case Textures::Down3:
    case Textures::Left3:
    case Textures::Right3:
    case Textures::Up3:
        return MainChar::Player3;

    case Textures::Standing4:
        return MainChar::Player4;
    case Textures::Standing5:
        return MainChar::Player5;
    }
    return MainChar::TypeCount;
}
MainChar::Type numToID(int num){
    switch (num)
    {
        case 0:
            return MainChar::Player1;
        case 1:
            return MainChar::Player2;
        case 2:
            return MainChar::Player3;
        case 3:
            return MainChar::Player4;
        case 4:
            return MainChar::Player5;
        default:
            break;
    }
    return MainChar::TypeCount;
}

int IDToNum(MainChar::Type type){
    switch (type)
    {
        case MainChar::Player1:
            return 0;
        case MainChar::Player2:
            return 1;
        case MainChar::Player3:
            return 2;
        case MainChar::Player4:
            return 3;
        case MainChar::Player5:
            return 4;
        default:
            break;
    }
    return MainChar::TypeCount;
}

MainChar::MainChar(Type type, TextureHolder& textures, int curLane, std::vector<Lane*>& lanes)
: textureHolder(textures)
, mType(type)
, upAnimation(textures.get(Table[type].upTexture))
, downAnimation(textures.get(Table[type].downTexture))
, leftAnimation(textures.get(Table[type].leftTexture))
, rightAnimation(textures.get(Table[type].rightTexture))
, ownerFlag(true)
, state(State::Standing)
, lanes(&lanes)
, lastPosSinceMoving(500, Lane::distanceBetweenLane * curLane)
, curLane(curLane)
, mHP(Table[type].hitpoints)
, maxHP(Table[type].hitpoints)
, mMP(0)
, maxMP(Table[type].manapoints)
, movingVelocity(Table[type].speed)
, timeSinceLastDamage()
{
    int frameWidth = Table[type].pictureWidth / Table[type].numOfFrames;
    int frameHeight = Table[type].pictureHeight;
    mSprite.setTexture(textures.get(Table[type].texture));
    mSprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    mSprite.scale(Table[type].scaling, Table[type].scaling);
    //centerOrigin(mSprite);

    setPosition(lastPosSinceMoving);
    setInLane();

    centerOrigin(upAnimation);
    upAnimation.setFrameSize(sf::Vector2i(frameWidth, frameHeight));
	upAnimation.setNumFrames(Table[type].numOfFrames);
	upAnimation.setDuration(sf::seconds(Table[type].timeEachFrameInGame));
    upAnimation.scale(Table[type].scaling, Table[type].scaling);
    
    centerOrigin(downAnimation);
    downAnimation.setFrameSize(sf::Vector2i(frameWidth, frameHeight));
	downAnimation.setNumFrames(Table[type].numOfFrames);
	downAnimation.setDuration(sf::seconds(Table[type].timeEachFrameInGame));
    downAnimation.scale(Table[type].scaling, Table[type].scaling);
    
    centerOrigin(leftAnimation);
    leftAnimation.setFrameSize(sf::Vector2i(frameWidth, frameHeight));
	leftAnimation.setNumFrames(Table[type].numOfFrames);
	leftAnimation.setDuration(sf::seconds(Table[type].timeEachFrameInGame));
    leftAnimation.scale(Table[type].scaling, Table[type].scaling);

    centerOrigin(rightAnimation);
    rightAnimation.setFrameSize(sf::Vector2i(frameWidth, frameHeight));
	rightAnimation.setNumFrames(Table[type].numOfFrames);
	rightAnimation.setDuration(sf::seconds(Table[type].timeEachFrameInGame));
    rightAnimation.scale(Table[type].scaling, Table[type].scaling);
}

MainChar::MainChar(Type type, TextureHolder& textures, sf::Vector2f pos)
: textureHolder(textures)
, mType(type)
, restAnimation(textures.get(Table[type].restTexture))
, maxHP(Table[type].hitpoints)
, mMP(0)
, maxMP(Table[type].manapoints)
, state(State::Rest)
, ownerFlag(true)
{
    setPosition(pos);

    int frameWidth = Table[type].pictureWidth / Table[type].numOfFrames;
    int frameHeight = Table[type].pictureHeight;
	centerOrigin(mSprite);
    mSprite.setTexture(textures.get(Table[type].texture));
    mSprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    mSprite.scale(Table[type].scaling, Table[type].scaling);

	centerOrigin(restAnimation);
    restAnimation.setFrameSize(sf::Vector2i(frameWidth, frameHeight));
	restAnimation.setNumFrames(Table[type].numOfFrames);
	restAnimation.setDuration(sf::seconds(Table[type].timeEachFrameInMenu));
    restAnimation.scale(Table[type].scaling, Table[type].scaling);
}

void MainChar::updateCurrent(sf::Time dt) {
    // Animation
    if(state == State::Rest) {
        restAnimation.setOwnerFlag(ownerFlag);
        restAnimation.update(dt);
        restAnimation.setRepeating(true);
        Entity::updateCurrent(dt);
        return;
    }
    int frameWidth = Table[mType].pictureWidth / Table[mType].numOfFrames;
    int frameHeight = Table[mType].pictureHeight;
    if(state == State::Up) {
        upAnimation.update(dt);
        upAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(0, frameHeight * state, frameWidth, frameHeight));
    }
    else if(state == State::Down) {
        downAnimation.update(dt);
        downAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(0, frameHeight * state, frameWidth, frameHeight));
    }
    else if(state == State::Left) {
        leftAnimation.update(dt);
        leftAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(0, frameHeight * state, frameWidth, frameHeight));
    }
    else if(state == State::Right) {
        rightAnimation.update(dt);
        rightAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(0, frameHeight * state, frameWidth, frameHeight));
    }

    // logic game
    makeStop();
    if(isStanding()) {
        setInLane();
    }
    Entity::updateCurrent(dt);
}

void MainChar::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    if(state == State::Rest) 
        target.draw(restAnimation, states);
    else if(state == State::Up)
        target.draw(upAnimation, states);
    else if(state == State::Down)
        target.draw(downAnimation, states);
    else if(state == State::Left)
        target.draw(leftAnimation, states);
    else if(state == State::Right)
        target.draw(rightAnimation, states);
    else
        target.draw(mSprite, states);
}

void MainChar::setTexture(Textures::ID id, const TextureHolder& textures)
{
    mType = toMainCharID(id);
    mSprite = sf::Sprite(textures.get(id));
    centerOrigin(mSprite);
}

auto MainChar::getTextureType() -> MainChar::Type{
    return mType;
}

Textures::ID MainChar::getTextureID(){
    return Table[mType].texture;
}

unsigned int MainChar::getCategory() const
{
	switch (mType)
	{
        case Player1:
		case Player2:
        case Player3:
        case Player4:
        case Player5:
			return Category::Player;

		default:
			return Category::None;
	}
}

sf::FloatRect MainChar::getBoundingRect() const {
    sf::FloatRect bound = getWorldTransform().transformRect(mSprite.getGlobalBounds());
    bound.left += Table[mType].deltaLeftBound;
    bound.height = std::min(bound.height, (float)Lane::distanceBetweenLane - 25);
    bound.width -= Table[mType].deltaWidthBound;
    return bound;
}

int MainChar::getHitpoints() const {
	return mHP;
}

int MainChar::getMaxHP() const {
    return maxHP;
}

int MainChar::getManaPoints() const {
    return mMP;
}

int MainChar::getMaxMP() const {
    return maxMP;
}

void MainChar::addMana(int points) {
    assert(points > 0);
    mMP += points;
    mMP = std::min(maxMP, mMP);
}

void MainChar::heal(int points) {
    assert(points > 0);
	mHP += points;
    mHP = std::min(maxHP, mHP);
}

void MainChar::damage(int points) {
	assert(points >= 0);
    sf::Time elapseTime = timeSinceLastDamage.getElapsedTime();
    if(elapseTime >= damageGap) {
	    mHP -= points;
        mHP = std::max(mHP, 0);
        timeSinceLastDamage.restart();
    }
}

bool MainChar::isDead() const {
	return mHP <= 0;
}

void MainChar::goUp() {
    setVelocity(0, -movingVelocity);
    state = State::Up;
}

void MainChar::goDown() {
    setVelocity(0, movingVelocity);
    state = State::Down;
}

void MainChar::goLeft() {
    setVelocity(-movingVelocity, 0);
    state = State::Left;
}

void MainChar::goRight() {
    setVelocity(movingVelocity, 0);
    state = State::Right;
}

void MainChar::stopMoving() {
    state = State::Standing;
    setVelocity(0, 0);
}

bool MainChar::isStanding() {
    return state == State::Standing;
}

void MainChar::useAbility() {
    if(canUseAbility()) {
        mMP -= maxMP;
    }
}

bool MainChar::canUseAbility() {
    return mMP == maxMP;
}

int MainChar::getCurLane() {
    return curLane;
}

void MainChar::setInLane() {
    setPosition(getPosition().x, (*lanes)[curLane]->getPosition().y + 25);
    lastPosSinceMoving = getPosition();
}

void MainChar::resetState() {
    setPosition(500, 0);
    curLane = 1;
    setInLane();
    lastPosSinceMoving = getPosition();
    state = State::Standing;
}

void MainChar::backTolastPos() {
    setPosition(lastPosSinceMoving);
}

void MainChar::makeStop() {
	sf::Vector2f newPos = getPosition();
	sf::Vector2f diff = lastPosSinceMoving - newPos;
    bool goUpDone = diff.y >= Lane::distanceBetweenLane - 1;
    bool goDownDone = diff.y <= -Lane::distanceBetweenLane + 1;
    bool goLeftDone = diff.x >= 10;
    bool goRightDone = diff.x <= -10;
	if(goUpDone) {
        ++curLane;
        stopMoving();
        lastPosSinceMoving = newPos;
	}
    else if(goDownDone) {
        --curLane;
        stopMoving();
        lastPosSinceMoving = newPos;
    }
    else if(goLeftDone || goRightDone) {
        stopMoving();
        lastPosSinceMoving = newPos;
    }
}

auto MainChar::getMainCharType() -> MainChar::Type{
    return mType;
}

int MainChar::getThisMaskID()
{
    return convertToMaskID(mType);
}

void MainChar::setOwnerFlag(bool flag)
{
    ownerFlag = flag;
    setOwnerShip(flag);
}

void MainChar::setCenterOriginMainChar()
{
    centerOrigin(mSprite);
    centerOrigin(restAnimation);
}

int convertToMaskID(MainChar::Type type)
{
    switch (type)
    {
        case MainChar::Player1:
            return Mask(0);
        case MainChar::Player2:
            return Mask(1);
        case MainChar::Player3:
            return Mask(2);
        case MainChar::Player4:
            return Mask(3);
        case MainChar::Player5:
            return Mask(4);
    }
    return 0;
}

MainChar::Type changeTexture(MainChar::Type type, bool isLeft){
    int shift = (isLeft) ? -1 : 1;
    int id = IDToNum(type);
    id = (id + shift + MainChar::TypeCount) % MainChar::TypeCount;
    MainChar::Type ans = numToID(id);
    return ans;
}

void MainChar::setOwnerShip(bool flag)
{
    if(ownerFlag)
        mSprite.setColor(sf::Color(255, 255, 255, 255));
    else 
        mSprite.setColor(sf::Color(0, 0, 0, 100));
}