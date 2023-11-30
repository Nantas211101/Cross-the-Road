#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
void setCenterOrigin(sf::Text &text);
void setCenterOrigin(sf::Sprite &sprite);
void setCenterOrigin(sf::CircleShape &shape, bool isCircle = false);

void setCenterOrigin(sf::RectangleShape &shape);
void setLeftCenterOrigin(sf::RectangleShape &shape);
void setTopCenterOrigin(sf::RectangleShape &shape);
void setRightCenterOrigin(sf::RectangleShape &shape);
void setDownCenterOrigin(sf::RectangleShape &shape);
