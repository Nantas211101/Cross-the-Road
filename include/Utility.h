#pragma once
#include <Animation.h>

#include <cmath>
#include <SFML/Graphics.hpp>

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(Animation& animation);
void centerOrigin(sf::Text& text);
float length(sf::Vector2f vector);