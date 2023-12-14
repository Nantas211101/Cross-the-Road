#pragma once

#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <Lane.hpp>
#include <Animal.hpp>
#include <Log.hpp>
#include <ResourceIdentifiers.hpp>
#include <Vehicle.hpp>
#include <Train.hpp>
#include <Decorator.hpp>
#include <Obstacle.hpp>
#include <MainChar.hpp>

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

struct DecoratorData {
	float speed;
	Textures::ID texture;
	sf::Vector2f scaling;
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
std::vector<DecoratorData> initializeDecoratorData();
std::vector<CharData> initializeCharData();