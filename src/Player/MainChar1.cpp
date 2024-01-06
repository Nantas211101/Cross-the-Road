#include <MainChar1.hpp>

MainChar1::MainChar1(TextureHolder& textures, CommandQueue& soundCommandQueue, int curLane, std::vector<Lane*>& lanes)
: MainChar(MainChar::Player1, textures, soundCommandQueue, curLane, lanes)
{}

MainChar1::MainChar1(TextureHolder& textures, sf::Vector2f pos)
: MainChar(MainChar::Player1, textures, pos)
{}

void MainChar1::updateCurrent(sf::Time dt) {
    MainChar::updateCurrent(dt);
    mMP = 0;
}