#include "../../include/World/Obstacle.h"

namespace{
    std::vector<ObstacleData> Table = initializeObstacleData();  
}


Obstacle::Obstacle(Type type, const TextureHolder& texture) 
: type(type)
, sprite(texture.get(Table[type].texture)) {
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(Table[type].scaling);
}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Obstacle::updateCurrent(sf::Time dt) {
    this->setVelocity(0, 0);
    Entity::updateCurrent(dt);
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

int Obstacle::getDamage(){
    return Table[type].dmg;
}
// sf::FloatRect* Obstacle::getDangerBound() const {
// 	sf::FloatRect tmp = getBoundingRect();
//     sf::FloatRect* pBound = new sf::FloatRect(tmp);
//     if(type == Obstacle::Obstacle1) {
//         delete pBound;
//         return nullptr;
//     }
//     tmp.top += 20;
//     tmp.left += 20;
//     tmp.width /= 6;
//     tmp.height /= 1.7;
//     return pBound;
// }