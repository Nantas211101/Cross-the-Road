#pragma once
#include "LaneFactory.h"

LaneFactory::LaneFactory(TextureHolder* textureHolder, sf::Vector2f startPos, int theme)
: lanes()
, textureHolder(textureHolder)
, startPos(startPos)
, theme(theme)
{}