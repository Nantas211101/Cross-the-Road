#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "TextureHolder.h"
#include "Lane.h"
#include "Animal.h"
#include "Log.h"
#include "TextureHolder.h"
#include "Vehicle.h"

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
	int pictureWidth;
	int pictureHeight;
	int numOfFrames;
};

struct VehicleData {
	float speed;
	int distanceBetweenVehicle;
	Textures::ID texture;
	sf::Vector2f scaling;
};

struct LaneData {
	float speed;
	Textures::ID texture;
};

std::vector<LogData> initializeLogData();
std::vector<AnimalData> initializeAnimalData();
std::vector<VehicleData> initializeVehicleData();