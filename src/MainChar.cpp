#include "../include/MainChar.h"

Textures::ID toTextureID(MainChar::Type type)
{
    switch (type)
    {
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
            return MainChar::Chicken;
            break;
        case 1:
            return MainChar::Penguin;
            break;
        case 2:
            return MainChar::Sheep;
            break;
        case 3:
            return MainChar::Mallard;
        default:
            break;
    }
    return MainChar::none;
}

int MainChar::IDToNum(Type type){
    switch (type)
    {
        case Chicken:
            return 0;
            break;
        case Penguin:
            return 1;
            break;
        case Sheep:
            return 2;
            break;
        case Mallard:
            return 3;
            break;
        default:
            break;
    }
    return 0;
}

MainChar::MainChar(Type type, const TextureHolder& textures, const FontHolder& fonts)
: mType(type)
, mSprite(textures.get(toTextureID(type)))
, mHP(100)
, mHealthDisplay(nullptr)
{
    mSprite.scale(0.05, 0.05);
    centerOrigin(mSprite);
    std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();
	this->attachChild(std::move(healthDisplay));
    updateTexts();
}

void MainChar::updateCurrent(sf::Time dt) {
    updateTexts();
    Entity::updateCurrent(dt);
}

void MainChar::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
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
