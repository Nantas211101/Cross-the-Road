#include "Lane.hpp"
#include "SFML/Graphics/Rect.hpp"
#include <Animal.hpp>

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
	sprite.setDuration(sf::seconds(Table[type].duration));
}   

Animal::Type Animal::getType(){
    return type;
}

unsigned int Animal::getCategory() const {
    return Category::Animal;
}

sf::FloatRect Animal::getBoundingRect() const {
    sf::FloatRect bound = getWorldTransform().transformRect(sprite.getGlobalBounds());
    bound.width -= Table[type].deltaWidthBound;
    bound.height = std::min(bound.height, (float)Lane::distanceBetweenLane);
    bound.left += Table[type].deltaLeftBound;;
    bound.top += Table[type].deltaHeightBound;
    return bound;
}

void Animal::drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const{
    target.draw(sprite, state);
}

void Animal::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    sprite.update(dt);
    sprite.setRepeating(true);
}

int Animal::getDamage(){
    return Table[type].dmg;
}