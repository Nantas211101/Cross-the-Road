#include <River.hpp>

River::River(TextureHolder* textureHolder, sf::Vector2f spawnPos, int difficulty)
: Lane(textureHolder, spawnPos, difficulty){}

unsigned int River::getCategory() const {
    return Category::River;
}

sf::FloatRect River::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}