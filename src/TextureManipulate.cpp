#include "TextureManipulate.hpp"

void setCenterOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void setCenterOrigin(sf::Sprite& sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void setCenterOrigin(sf::CircleShape& shape, bool isCircle) {
    sf::FloatRect bounds = shape.getLocalBounds();
    if (!isCircle)
        shape.setOrigin(bounds.height * 2.f / 3.f, bounds.width / 2.f);
    else
        shape.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void setCenterOrigin(sf::RectangleShape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void setLeftCenterOrigin(sf::RectangleShape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(0, bounds.height / 2.f);
}

void setTopCenterOrigin(sf::RectangleShape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(bounds.width / 2.f, 0);
}

void setRightCenterOrigin(sf::RectangleShape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(bounds.width, bounds.height / 2.f);
}

void setDownCenterOrigin(sf::RectangleShape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(bounds.width / 2.f, bounds.height);
}