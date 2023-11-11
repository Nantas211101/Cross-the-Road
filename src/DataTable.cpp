#include "../include/DataTable.h"
#include "../include/Log.h"
#include "../include/Lane.h"

std::vector<LogData> initializeLogData() {
    std::vector<LogData> data(Log::TypeCount);
    data[Log::Log1].speed = 40.f;
    data[Log::Log1].texture = Textures::Log;
    data[Log::Log1].scaling = sf::Vector2f(0.4, 0.4);

    data[Log::Crocodile].speed = 60.f;
    data[Log::Crocodile].texture = Textures::Log;
    return data;
}

std::vector<LaneData> initializeLaneData() {
    std::vector<LaneData> data(Lane::TypeCount);
    data[Lane::Ground].speed = 0;
    data[Lane::Ground].texture = Textures::Ground;

    data[Lane::Road].speed = 0;
    data[Lane::Road].texture = Textures::Road;

    data[Lane::River].speed = 20.f;
    data[Lane::River].texture = Textures::River;
    return data;
}