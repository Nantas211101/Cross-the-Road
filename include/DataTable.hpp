#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceIdentifiers.hpp"
// #include "Lane.h"
#include <vector>

struct LogData {
	float speed;
	int distanceBetweenLog;
	Textures::ID texture;
	sf::Vector2f scaling;
};
struct AnimalData {
	float speed;
	int distanceBetweenAnimal;
	Textures::ID texture;
	sf::Vector2f scaling;
};

struct LaneData {
	float speed;
	Textures::ID texture;
};

struct CharData { // Thinh adding
    int hitpoints;
    float speed;
    Textures::ID texture;
};


// std::vector<LogData> initializeLogData();
// std::vector<AnimalData> initializeAnimalData();
std::vector<CharData> initializeCharData(); // Thinh adding