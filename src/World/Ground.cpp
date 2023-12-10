#include "../../include/World/Ground.h"

#include <iostream>

// 50: width each lane

Ground::Ground(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: Lane(textureHolder, spawnPos){}