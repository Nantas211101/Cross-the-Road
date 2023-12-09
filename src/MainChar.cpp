#include "../include/MainChar.h"

Textures::ID toTextureID(MainChar::Type type)
{
    switch (type)
    {
    case MainChar::Player1:
        return Textures:: Player1Up;
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
    case Textures::Player1Up:
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

MainChar::MainChar(Type type, const TextureHolder& textures, const FontHolder& fonts)
: mType(type)
, mSprite(textures.get(toTextureID(type)))
, upAnimation(textures.get(Textures::Up1))
, downAnimation(textures.get(Textures::Down1))
, leftAnimation(textures.get(Textures::Left1))
, rightAnimation(textures.get(Textures::Right1))
, mHP(100)
, mHealthDisplay(nullptr)
, isGoingUp(false)
, isGoingDown(false)
, isGoingLeft(false)
, isGoingRight(false)
{
    mSprite.scale(1, 1);
    //centerOrigin(mSprite);
    std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();

    //upAnimation.setOrigin(this->getPosition().x / 2.f, this->getPosition().y / 2.f);
    centerOrigin(upAnimation);
    upAnimation.setFrameSize(sf::Vector2i(256 / 4, 56));
	upAnimation.setNumFrames(4);
	upAnimation.setDuration(sf::seconds(1));
	
    this->attachChild(std::move(healthDisplay));
    updateTexts();
}

void MainChar::updateCurrent(sf::Time dt) {
    if(isGoingUp) {
        upAnimation.update(dt);
        upAnimation.setRepeating(true);
    }
    updateTexts();
    Entity::updateCurrent(dt);
}

void MainChar::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    if(isGoingUp) {
        target.draw(upAnimation, states);
    }
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
    isGoingUp = true;
}

void MainChar::goDown() {
    setVelocity(0, movingVelocity);
    isGoingUp = true;
}

void MainChar::goLeft() {
    setVelocity(-movingVelocity, 0);
    isGoingUp = true;
}

void MainChar::goRight() {
    setVelocity(movingVelocity, 0);
    isGoingUp = true;
}

void MainChar::stop() {
    setVelocity(0, 0);
    isGoingUp = false;
    isGoingDown = false;
    isGoingLeft = false;
    isGoingRight = false;
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
