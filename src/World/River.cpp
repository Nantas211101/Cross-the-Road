#include <River.hpp>

River::River(TextureHolder* textureHolder, sf::Vector2f spawnPos, int difficulty, bool reverse)
: Lane(textureHolder, spawnPos, difficulty, reverse){}

unsigned int River::getCategory() const {
    return Category::River;
}

sf::FloatRect River::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}