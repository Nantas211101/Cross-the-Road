#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"
#include <vector>

struct LogData {
	float speed;
	int distanceBetweenLog;
	Textures::ID texture;
	sf::Vector2f scaling;
};

std::vector<LogData> initializeLogData();