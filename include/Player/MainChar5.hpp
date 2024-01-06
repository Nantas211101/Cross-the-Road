#pragma once

#include <MainChar.hpp>
#include <SpriteNode.hpp>
#include <MainChar1.hpp>

class MainChar5 : public MainChar {
private:
    void updateCurrent(sf::Time dt);

public:
    MainChar5(TextureHolder& textures, CommandQueue& soundCommandQueue, int curLane, std::vector<Lane*>& lanes);
    MainChar5(TextureHolder& textures, sf::Vector2f pos);
    void useAbility();

private:
    int lastHealth;
    const int accelerateAmount = 100;

    SpriteNode* powerShell;
    bool isAttach;
    sf::Clock AbilityTime;
    const sf::Time AbilityLength = sf::seconds(5);
};