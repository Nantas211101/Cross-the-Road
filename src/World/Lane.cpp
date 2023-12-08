#include "../../include/World/Lane.h"

Lane::Lane(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: textureHolder(textureHolder)
, startPos(spawnPos)
{
    //random 2 -> 5 lane
    //numOfLane = 2 + rand() % 3;
    reverse = rand() % 2;

}

bool Lane::isReverse() {
    return reverse;
}

void Lane::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}