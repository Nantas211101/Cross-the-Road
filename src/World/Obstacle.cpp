#include "../../include/World/Obstacle.h"


Obstacle::Obstacle(const TextureHolder& texture) 
: sprite(texture.get(Textures::Obstacle)) {
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(0.5f,0.5f);
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