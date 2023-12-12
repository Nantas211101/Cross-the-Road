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
#include "MainChar.h"

struct LogData {
	float speed;
	int distanceBetweenLog;
	Textures::ID texture;
	sf::Vector2f scaling;
};

struct ObstacleData {
	float speed;
	int dmg;
	Textures::ID texture;
	sf::Vector2f scaling;
	int pictureWidth;
	int pictureHeight;
	int numOfFrames;
};

struct AnimalData {
	int dmg;
	float speed;
	int distanceBetweenAnimal;
	Textures::ID texture;
	sf::Vector2f scaling;
	int pictureWidth;
	int pictureHeight;
	int numOfFrames;
};

struct VehicleData {
	int dmg;
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

struct CharData {
    int hitpoints;
    float speed;
    Textures::ID texture;
    Textures::ID upTexture;
    Textures::ID downTexture;
    Textures::ID leftTexture;
    Textures::ID rightTexture;
	int pictureWidth;
	int pictureHeight;
	int numOfFrames;
	float timeEachFrame;
};


std::vector<LogData> initializeLogData();
std::vector<AnimalData> initializeAnimalData();
std::vector<VehicleData> initializeVehicleData();
std::vector<TrainData> initializeTrainData();
std::vector<ObstacleData> initializeObstacleData();
std::vector<CharData> initializeCharData();