#include "../include/MainChar.h"

Textures::ID toTextureID(MainChar::Type type)
{
    switch (type)
    {
    case MainChar::Player1:
        return Textures:: Standing1;
    case MainChar::Chicken:
        return Textures::Chicken;
    case MainChar::Penguin:
        return Textures::Penguin;
    case MainChar::Sheep:
        return Textures::Sheep;
    case MainChar::Mallard:
        return Textures::Mallard;
    }
    return Textures::none;
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

MainChar::MainChar(Type type, const TextureHolder& textures, const FontHolder& fonts, sf::Vector2f spawnPos)
: mType(type)
, upAnimation(textures.get(Textures::Up1))
, downAnimation(textures.get(Textures::Down1))
, leftAnimation(textures.get(Textures::Left1))
, rightAnimation(textures.get(Textures::Right1))
, mHP(100)
, mHealthDisplay(nullptr)
, state(State::Standing)
{
    mSprite.setTexture(textures.get(Textures::Standing1));
    mSprite.setTextureRect(sf::IntRect(0, 0, 239 / 4, 56));
    //centerOrigin(mSprite);
    
    lastPosSinceMoving = spawnPos;

    std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();

    centerOrigin(upAnimation);
    upAnimation.setFrameSize(sf::Vector2i(256 / 4, 56));
	upAnimation.setNumFrames(4);
	upAnimation.setDuration(sf::seconds(0.5));
    
    centerOrigin(downAnimation);
    downAnimation.setFrameSize(sf::Vector2i(256 / 4, 56));
	downAnimation.setNumFrames(4);
	downAnimation.setDuration(sf::seconds(0.5));
    
    centerOrigin(leftAnimation);
    leftAnimation.setFrameSize(sf::Vector2i(256 / 4, 56));
	leftAnimation.setNumFrames(4);
	leftAnimation.setDuration(sf::seconds(0.5));

    centerOrigin(rightAnimation);
    rightAnimation.setFrameSize(sf::Vector2i(256 / 4, 56));
	rightAnimation.setNumFrames(4);
	rightAnimation.setDuration(sf::seconds(0.5));
	
    this->attachChild(std::move(healthDisplay));
    updateTexts();
}

void MainChar::updateCurrent(sf::Time dt) {
    if(state == State::Up) {
        upAnimation.update(dt);
        upAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(239 / 4 * state, 0, 239 / 4, 56));
    }
    else if(state == State::Down) {
        downAnimation.update(dt);
        downAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(239 / 4 * state, 0, 239 / 4, 56));
    }
    else if(state == State::Left) {
        leftAnimation.update(dt);
        leftAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(239 / 4 * state, 0, 239 / 4, 56));
    }
    else if(state == State::Right) {
        rightAnimation.update(dt);
        rightAnimation.setRepeating(true);
        mSprite.setTextureRect(sf::IntRect(239 / 4 * state, 0, 239 / 4, 56));
    }
    stop();
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
    mSprite = sf::Sprite(textures.get(toTextureID(mType)));
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
    return toTextureID(mType);
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

void MainChar::stop() {
	sf::Vector2f newPos = getPosition();
	sf::Vector2f diff = lastPosSinceMoving - newPos;
	if(diff.y >= Lane::distanceBetweenLane ||
       diff.y <= -Lane::distanceBetweenLane || 
       diff.x >= 150 ||
       diff.x <= -150) 
    {
        state = State::Standing;
        setVelocity(0, 0);
		lastPosSinceMoving = newPos;
	}
}

void MainChar::updateTexts()
{
	mHealthDisplay->setString(std::to_string(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());

	// if (mMissileDisplay)
	// {
	// 	if (mMissileAmmo == 0)
	// 		mMissileDisplay->setString("");
	// 	else
	// 		mMissileDisplay->setString("M: " + to_string(mMissileAmmo));
	// }
}
