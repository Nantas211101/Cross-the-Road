#pragma once

#include <MainChar.hpp>
#include <SpriteNode.hpp>

class Player2 : public MainChar {
private:
    void updateCurrent(sf::Time dt);

public:
    Player2(TextureHolder& textures, int curLane, std::vector<Lane*>& lanes);
    Player2(TextureHolder& textures, sf::Vector2f pos);
    void useAbility();

private:
    TextureHolder& textureHolder;

    bool abilityActive;
    bool isAttach;
    sf::Clock AbilityTime;
    const int accelerateAmount = 100;
    const sf::Time AbilityLength = sf::seconds(5);
    SpriteNode* powerShell;
};