#include "../include/River.h"

River::River(const TextureHolder& texture) 
: sprite(texture.get(Textures::River))
, riverLog()
{}

River::River(const TextureHolder& texture, const sf::IntRect& textureRect)
: sprite(texture.get(Textures::River), textureRect)
, riverLog()
{}

void River::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void River::updateCurrent(sf::Time dt) {
    this->setVelocity(10.f, 0);
    Entity::updateCurrent(dt);
}