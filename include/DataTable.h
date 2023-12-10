#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "World/Lane.h"
#include "World/Animal.h"
#include "World/Log.h"
#include "ResourceIdentifiers.h"
#include "World/Vehicle.h"
#include "World/Train.h"
#include "World/Obstacle.h"

struct LogData {
	float speed;
	int distanceBetweenLog;
	Textures::ID texture;
	sf::Vector2f scaling;
};

struct ObstacleData {
	float speed;
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

struct TrainData{
	float speed;
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
std::vector<TrainData> initializeTrainData();
std::vector<ObstacleData> initializeObstacleData();