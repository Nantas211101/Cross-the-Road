#include <Lane.hpp>

Lane::Lane(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: textureHolder(textureHolder)
, startPos(spawnPos)
{
    reverse = rand() % 2;
}

bool Lane::isReverse() {
    return reverse;
}

void Lane::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}