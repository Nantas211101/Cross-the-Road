#include "MainChar.hpp"
#include "TextureManipulate.hpp"
#include "DataTable.hpp"

namespace 
{
    const std::vector<CharData> Table = initializeCharData();
}

Textures::ID MainChar::toTextureID(MainChar::Type type)
{
    return Table[type].texture;
    // switch (type)
    // {
    // case MainChar::Chicken:
    //     return Textures::chicken;
    // case MainChar::Penguin:
    //     return Textures::penguin;
    // case MainChar::Sheep:
    //     return Textures::sheep;
    // case MainChar::Mallard:
    //     return Textures::mallard;
    // }
    // return Textures::none;
}

MainChar::Type toMainCharID(Textures::ID id)
{
    switch (id)
    {
    case Textures::chicken:
        return MainChar::Chicken;
    case Textures::penguin:
        return MainChar::Penguin;
    case Textures::sheep:
        return MainChar::Sheep;
    case Textures::mallard:
        return MainChar::Mallard;
    }
    return MainChar::TypeCount;
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
    return MainChar::TypeCount;
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

MainChar::MainChar(Type type, const TextureHolder& textures)
: mType(type)
, mSprite(textures.get(toTextureID(type)))
{
    setCenterOrigin(mSprite);
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
    setCenterOrigin(mSprite);
}

void MainChar::setTexture(Textures::ID id, const TextureHolder& textures)
{
    mType = toMainCharID(id);
    mSprite = sf::Sprite(textures.get(id));
    setCenterOrigin(mSprite);
}


auto MainChar::getMainCharType() -> MainChar::Type{
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
			return Category::PlayerAircraft;

		default:
			return Category::EnemyAircraft;
	}
}