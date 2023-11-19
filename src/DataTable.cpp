#include "../include/DataTable.h"
#include "../include/Log.h"
#include "../include/Lane.h"

std::vector<LogData> initializeLogData() {
    std::vector<LogData> data(Log::TypeCount);
    data[Log::Log1].speed = 200.f;
    data[Log::Log1].distanceBetweenLog = 600;
    data[Log::Log1].texture = Textures::Log;
    data[Log::Log1].scaling = sf::Vector2f(0.8, 0.4);

    data[Log::Log2].speed = 200.f;
    data[Log::Log2].distanceBetweenLog = 1000;
    data[Log::Log2].texture = Textures::Log;
    data[Log::Log2].scaling = sf::Vector2f(1.2, 0.4);

    data[Log::Log3].speed = 200.f;
    data[Log::Log3].distanceBetweenLog = 500;
    data[Log::Log3].texture = Textures::Log;
    data[Log::Log3].scaling = sf::Vector2f(0.6, 0.4);

    data[Log::Crocodile].speed = 60.f;
    data[Log::Crocodile].texture = Textures::Log;
    return data;
}