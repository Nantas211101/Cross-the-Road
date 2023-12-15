#pragma once

#include <Animation.hpp>

#include <cmath>
#include <sstream>
#include <SFML/Graphics.hpp>

namespace sf
{
	class Sprite;
	class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);


void centerOrigin(sf::Sprite& sprite);
void centerOrigin(Animation& animation);
void centerOrigin(sf::Text& text);
float length(sf::Vector2f vector);

#include <Utility.inl>