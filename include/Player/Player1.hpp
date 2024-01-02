#pragma once

#include <MainChar.hpp>

class Player1 : public MainChar {
public:
    Player1(const TextureHolder& textures, int curLane, std::vector<Lane*>& lanes);
    Player1(const TextureHolder& textures, sf::Vector2f pos);
    void useAbility();

private:
    const int healingPoint = 10;
};