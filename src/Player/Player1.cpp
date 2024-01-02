#include <Player1.hpp>

Player1::Player1(const TextureHolder& textures, int curLane, std::vector<Lane*>& lanes)
: MainChar(MainChar::Player1, textures, curLane, lanes)
{}

Player1::Player1(const TextureHolder& textures, sf::Vector2f pos)
: MainChar(MainChar::Player1, textures, pos)
{}

void Player1::useAbility() {
    if(canUseAbility()) {
        MainChar::useAbility();
        heal(healingPoint);
    }
}