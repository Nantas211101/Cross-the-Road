#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"
#include <vector>

struct LogData {
	sf::Vector2f scaling;
	float speed;
	Textures::ID texture;
};

struct LaneData {
	float speed;
	Textures::ID texture;
};

std::vector<LogData> initializeLogData();
std::vector<LaneData> initalizeLaneData();