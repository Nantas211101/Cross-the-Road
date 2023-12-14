#include <MainChar.hpp>

namespace {
    const std::vector<CharData> Table = initializeCharData();
}

MainChar::Type toMainCharID(Textures::ID id)
{
    switch (id)
    {
    case Textures::Standing1:
        return MainChar::Player1;
    case Textures::Chicken:
        return MainChar::Chicken;
    case Textures::Penguin:
        return MainChar::Penguin;
    case Textures::Sheep:
        return MainChar::Sheep;
    case Textures::Mallard:
        return MainChar::Mallard;
    }
    return MainChar::none;
}
MainChar::Type MainChar::numToID(int num){
    switch (num)
    {
        case 0:
            return MainChar::Player1;
            break;
        case 1:
            return MainChar::Chicken;
            break;
        case 2:
            return MainChar::Penguin;
            break;
        case 3:
            return MainChar::Sheep;
            break;
        case 4:
            return MainChar::Mallard;
        default:
            break;
    }
    return MainChar::none;
}

int MainChar::IDToNum(Type type){
    switch (type)
    {
        case Player1:
            return 0;
            break;
        case Chicken:
            return 1;
            break;
        case Penguin:
            return 2;
            break;
        case Sheep:
            return 3;
            break;
        case Mallard:
            return 4;
            break;
        default:
            break;
    }
    return 0;
}

MainChar::MainChar(Type type, const TextureHolder& textures, const FontHolder& fonts, int curLane, const std::vector<Lane*>& lanes)
: mType(type)
, upAnimation(textures.get(Table[type].upTexture))
, downAnimation(textures.get(Table[type].downTexture))
, leftAnimation(textures.get(Table[type].leftTexture))
, rightAnimation(textures.get(Table[type].rightTexture))
, mHP(Table[type].hitpoints)
, mHealthDisplay(nullptr)
, lastPosSinceMoving(410, 0)
, state(State::Standing)
, curLane(curLane)
{
    int frameWidth = Table[type].pictureWidth / Table[type].numOfFrames;
    int frameHeight = Table[type].pictureHeight;
    mSprite.setTexture(textures.get(Textures::Standing1));
    mSprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    //centerOrigin(mSprite);

    setPosition(lastPosSinceMoving);
    setInLane(lanes);

    std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();

    //centerOrigin(upAnimation);
    upAnimation.setFrameSize(sf::Vector2i(frameWidth, frameHeight));
	upAnimation.setNumFrames(Table[type].numOfFrames);
	upAnimation.setDuration(sf::seconds(Table[type].timeEachFrame));
    
    centerOrigin(downAnimation);
    downAnimation.setFrameSize(sf::Vector2i(frameWidth, frameHeight));
	downAnimation.setNumFrames(Table[type].numOfFrames);
	downAnimation.setDuration(sf::seconds(Table[type].timeEachFrame));
    
    centerOrigin(leftAnimation);
    leftAnimation.setFrameSize(sf::Vector2i(frameWidth, frameHeight));
	leftAnimation.setNumFrames(Table[type].numOfFrames);
	leftAnimation.setDuration(sf::seconds(Table[type].timeEachFrame));

    centerOrigin(rightAnimation);
    rightAnimation.setFrameSize(sf::Vector2i(frameWidth, frameHeight));
	rightAnimation.setNumFrames(Table[type].numOfFrames);
	rightAnimation.setDuration(sf::seconds(Table[type].timeEachFrame));
	
    this->attachChild(std::move(healthDisplay));
    updateTexts();
}

void MainChar::updateCurrent(sf::Time dt) {
    int frameWidth = Table[mType].pictureWidth / Table[mType].numOfFrames;
    int frameHeight = Table[mType].pictureHeight;
    if(state == State::Up) {
        upAnimation.update(dt);
        upAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(frameWidth * state, 0, frameWidth, frameHeight));
    }
    else if(state == State::Down) {
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
    if(state == State::Up)
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

void MainChar::changeTexture(bool isIncrease, const TextureHolder& textures){
    int id = IDToNum(mType);
    if(isIncrease)
        ++id;
    else 
        --id;
    id = (id + 4) % 4;
    mType = numToID(id);
    mSprite = sf::Sprite(textures.get(Table[mType].texture));
    centerOrigin(mSprite);
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
		case Chicken:
        case Penguin:
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
    prevLane = curLane;
    ++curLane;
}

void MainChar::goDown() {
    setVelocity(0, movingVelocity);
    state = State::Down;
    prevLane = curLane;
    --curLane;
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
    if(state == State::Standing)
        return true;
    return false;
}

sf::Vector2f MainChar::getLastPos() {
    return lastPosSinceMoving;
}

void MainChar::alignChar() {
    sf::Vector2f pos = getPosition();
    setPosition((pos.x + Lane::distanceBetweenTile / 2) / Lane::distanceBetweenTile * Lane::distanceBetweenTile, pos.y);
}

int MainChar::getCurLane() {
    return curLane;
}

void MainChar::setInLane(const std::vector<Lane*>& lanes) {
    setPosition(getPosition().x, lanes[curLane]->getPosition().y + 25);
}

void MainChar::resetState() {
    curLane = 0;
    state = State::Standing;
}

void MainChar::backTolastLane() {
    curLane = prevLane;
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
