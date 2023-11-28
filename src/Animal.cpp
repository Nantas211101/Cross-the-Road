#include "../include/Animal.h"

namespace{
    std::vector<AnimalData> Table = initializeAnimalData();  
}

Animal::Animal(Type type, const TextureHolder& texture)
: type(type)
, sprite(texture.get(Table[type].texture)){
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setFrameSize(sf::Vector2i(Table[type].pictureWidth/Table[type].numOfFrames, Table[type].pictureHeight));
	sprite.setNumFrames(Table[type].numOfFrames);
	sprite.setDuration(sf::seconds(1));
}   

Animal::Type Animal::getType(){
    return type;
}

void Animal::drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const{
    target.draw(sprite, state);
}

void Animal::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    sprite.update(dt);
    sprite.setRepeating(true);
}