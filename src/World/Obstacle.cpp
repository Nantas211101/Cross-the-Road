#include <Obstacle.h>

namespace{
    std::vector<ObstacleData> Table = initializeObstacleData();  
}


Obstacle::Obstacle(Type type, const TextureHolder& texture) 
: type(type)
, sprite(texture.get(Table[type].texture)) {
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(Table[type].scaling);
    sprite.setFrameSize(sf::Vector2i(Table[type].pictureWidth/Table[type].numOfFrames, Table[type].pictureHeight));
	sprite.setNumFrames(Table[type].numOfFrames);
	sprite.setDuration(sf::seconds(1));
}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Obstacle::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    sprite.update(dt);
    sprite.setRepeating(true);
}

sf::FloatRect Obstacle::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

Obstacle::Type Obstacle::getType() {
    return type;
}

unsigned int Obstacle::getCategory() const {
    return Category::Obstacle;
}

int Obstacle::getDamage() {
    return Table[type].dmg;
}