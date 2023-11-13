#include "../include/Grass.h"

Grass::Grass(const TextureHolder& texture) 
: sprite(texture.get(Textures::Grass))
{}

Grass::Grass(const TextureHolder& texture, const sf::IntRect& textureRect)
: sprite(texture.get(Textures::Grass), textureRect)
{}

void Grass::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Grass::updateCurrent(sf::Time dt) {
    this->setVelocity(0, 0);
    Entity::updateCurrent(dt);
}