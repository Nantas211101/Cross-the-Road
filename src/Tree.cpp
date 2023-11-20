#include "../include/Tree.h"


Tree::Tree(const TextureHolder& texture) 
: sprite(texture.get(Textures::Tree)) {
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(0.5f,0.5f);
}

void Tree::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Tree::updateCurrent(sf::Time dt) {
    this->setVelocity(0, 0);
    Entity::updateCurrent(dt);
}

sf::FloatRect Tree::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

// sf::FloatRect* Tree::getDangerBound() const {
// 	sf::FloatRect tmp = getBoundingRect();
//     sf::FloatRect* pBound = new sf::FloatRect(tmp);
//     if(type == Tree::Tree1) {
//         delete pBound;
//         return nullptr;
//     }
//     tmp.top += 20;
//     tmp.left += 20;
//     tmp.width /= 6;
//     tmp.height /= 1.7;
//     return pBound;
// }