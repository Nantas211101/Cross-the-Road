#pragma once

#include <MainChar.hpp>

class MainChar1 : public MainChar {
private:
    void updateCurrent(sf::Time dt);
public:
    MainChar1(TextureHolder& textures, int curLane, std::vector<Lane*>& lanes);
    MainChar1(TextureHolder& textures, sf::Vector2f pos);
};