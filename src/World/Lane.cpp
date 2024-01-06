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

unsigned int Lane::getCategory() const {
    return Category::Lane;
}

void Lane::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(animation, states);
    target.draw(sprite, states);
}

sf::FloatRect Lane::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}