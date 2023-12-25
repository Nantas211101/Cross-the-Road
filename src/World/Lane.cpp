#include <Lane.hpp>

Lane::Lane(TextureHolder* textureHolder, sf::Vector2f spawnPos, int difficulty)
: textureHolder(textureHolder)
, startPos(spawnPos)
, difficulty(difficulty)
{
    reverse = rand() % 2;
}

bool Lane::isReverse() {
    return reverse;
}

void Lane::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(animation, states);
    target.draw(sprite, states);
    
}

sf::Vector2f Lane::transformVelocity(sf::Vector2f v){
    if (difficulty>3){
        v.x *= 1.2;
        v.y *= 1.2;
    }
    return v;
}