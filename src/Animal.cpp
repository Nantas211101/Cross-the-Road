#include "Animal.h"
#include "DataTable.h"
#include "TextureHolder.h"

namespace{
    std::vector<AnimalData> Table = initializeAnimalData();  
}

Animal::Animal(Type type, const TextureHolder& texture)
: type(type)
, sprite(texture.get(Table[type].texture)){
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}   

Animal::Type Animal::getType(){
    return type;
}

void Animal::drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const{
    target.draw(sprite, state);
}

void Animal::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
}