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

    case Textures::Sheep:
        return MainChar::Sheep;
    case Textures::Mallard:
        return MainChar::Mallard;
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
            return MainChar::Sheep;
        case 4:
            return MainChar::Mallard;
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
        case MainChar::Sheep:
            return 3;
        case MainChar::Mallard:
            return 4;
        default:
            break;
    }
    return MainChar::TypeCount;
}

MainChar::MainChar(Type type, const TextureHolder& textures, const FontHolder& fonts, int curLane, int curGrid, const std::vector<Lane*>& lanes)
: mType(type)
, upAnimation(textures.get(Table[type].upTexture))
, downAnimation(textures.get(Table[type].downTexture))
, leftAnimation(textures.get(Table[type].leftTexture))
, rightAnimation(textures.get(Table[type].rightTexture))
, mHP(Table[type].hitpoints)
, mHealthDisplay(nullptr)
, curLane(curLane)
, curGrid(curGrid)
, prevLane(curLane)
, prevGrid(curGrid)
, lastPosSinceMoving(Lane::distanceBetweenTile * curGrid, Lane::distanceBetweenLane * curLane)
, state(State::Standing)
, ownerFlag(true)
{
    int frameWidth = Table[type].pictureWidth / Table[type].numOfFrames;
    int frameHeight = Table[type].pictureHeight;
    mSprite.setTexture(textures.get(Table[type].texture));
    mSprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    mSprite.scale(Table[type].scaling, Table[type].scaling);
    //centerOrigin(mSprite);

    setPosition(lastPosSinceMoving);
    setInLane(lanes);
    setInGrid();

    std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();

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
	
    this->attachChild(std::move(healthDisplay));
    updateTexts();
}

MainChar::MainChar(Type type, const TextureHolder& textures, sf::Vector2f pos)
: mType(type)
, restAnimation(textures.get(Table[type].restTexture))
, mHP(Table[type].hitpoints)
, mHealthDisplay(nullptr)
, lastPosSinceMoving(pos)
, state(State::Rest)
, curLane()
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
        mSprite.setTextureRect(sf::IntRect(frameWidth * state, 0, frameWidth, frameHeight));
    }
    else if(state == State::Down) {
        downAnimation.setOwnerFlag(ownerFlag);
        downAnimation.update(dt);
        downAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(frameWidth * state, 0, frameWidth, frameHeight));
    }
    else if(state == State::Left) {
        leftAnimation.update(dt);
        leftAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(frameWidth * state, 0, frameWidth, frameHeight));
    }
    else if(state == State::Right) {
        rightAnimation.update(dt);
        rightAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(frameWidth * state, 0, frameWidth, frameHeight));
    }
    makeStop();
    updateTexts();
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
        case Sheep:
        case Mallard:
			return Category::Player;

		default:
			return Category::None;
	}
}

sf::FloatRect MainChar::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

int MainChar::getHitpoints() const {
	return mHP;
}

void MainChar::heal(int points) {
	assert(points > 0);

	mHP += points;
}

void MainChar::damage(int points) {
	assert(points > 0);

	mHP -= points;
}

void MainChar::destroy() {
	mHP = 0;
}

bool MainChar::isDestroyed() const {
	return mHP <= 0;
}

void MainChar::goUp() {
    setVelocity(0, -movingVelocity);
    state = State::Up;
    prevGrid = curGrid;
    prevLane = curLane;
    ++curLane;
}

void MainChar::goDown() {
    setVelocity(0, movingVelocity);
    state = State::Down;
    prevGrid = curGrid;
    prevLane = curLane;
    --curLane;
}

void MainChar::goLeft() {
    setVelocity(-movingVelocity, 0);
    state = State::Left;
    prevLane = curLane;
    prevGrid = curGrid;
    --curGrid;
}

void MainChar::goRight() {
    setVelocity(movingVelocity, 0);
    state = State::Right;
    prevLane = curLane;
    prevGrid = curGrid;
    ++curGrid;
}

void MainChar::stopMoving() {
    state = State::Standing;
    setVelocity(0, 0);
}

bool MainChar::isStanding() {
    if(state == State::Standing)
        return true;
    return false;
}

sf::Vector2f MainChar::getLastPos() {
    return lastPosSinceMoving;
}

int MainChar::getCurLane() {
    return curLane;
}

void MainChar::setInLane(const std::vector<Lane*>& lanes) {
    setPosition(getPosition().x, lanes[curLane]->getPosition().y + 25);
}

void MainChar::setInGrid() {
    setPosition(Lane::distanceBetweenTile * curGrid + 15, getPosition().y);
}

void MainChar::fixInPos(const std::vector<Lane*>& lanes) {
    setInLane(lanes);
    setInGrid();
}

void MainChar::resetState() {
    curLane = 0;
    prevLane = 0;
    curGrid = 5;
    prevGrid = 5;
    state = State::Standing;
}

void MainChar::backTolastPos(const std::vector<Lane*>& lanes) {
    curLane = prevLane;
    curGrid = prevGrid;
    fixInPos(lanes);
    lastPosSinceMoving = getPosition();
}

void MainChar::makeStop() {
	sf::Vector2f newPos = getPosition();
	sf::Vector2f diff = lastPosSinceMoving - newPos;
	if(diff.y >= Lane::distanceBetweenLane - 1 ||
       diff.y <= -Lane::distanceBetweenLane + 1 || 
       diff.x >= Lane::distanceBetweenTile - 1 ||
       diff.x <= -Lane::distanceBetweenTile + 1) 
    {
        stopMoving();
        lastPosSinceMoving = newPos;
	}
}

void MainChar::updateTexts()
{
	mHealthDisplay->setString(std::to_string(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());
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
            break;
        case MainChar::Player2:
            return Mask(1);
            break;
        case MainChar::Player3:
            return Mask(2);
            break;
        case MainChar::Mallard:
            return Mask(3);
            break;
        default:
            break;
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

void MainChar::whatIsCurrentState()
{
    switch (state)
    {
        case State::Up:
            std::cerr << "Up" << std::endl;
            break;
        
        case State::Down:
            std::cerr << "Down" << std::endl;
            break;
        
        case State::Left:
            std::cerr << "Left" << std::endl;
            break;

        case State::Right:
            std::cerr << "Right" << std::endl;
            break;

        case State::Standing:
            std::cerr << "Standing" << std::endl;
            break;
        
        default:
            break;
    }
    // std::cout << "Current state: " << state << std::endl;
}

void MainChar::setOwnerShip(bool flag)
{
    if(ownerFlag)
        mSprite.setColor(sf::Color(255, 255, 255, 255));
    else 
        mSprite.setColor(sf::Color(0, 0, 0, 100));
}