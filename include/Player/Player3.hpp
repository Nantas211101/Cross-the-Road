#pragma once

#include <MainChar.hpp>
#include <SpriteNode.hpp>

class Player3 : public MainChar {
private:
    void updateCurrent(sf::Time dt);

public:
    Player3(TextureHolder& textures, int curLane, std::vector<Lane*>& lanes);
    Player3(TextureHolder& textures, sf::Vector2f pos);
    void useAbility();

private:
    TextureHolder& textureHolder;

    bool abilityActive;
    bool isAttach;
    sf::Clock AbilityTime;
    int lastHealth;
    const sf::Time AbilityLength = sf::seconds(5);
    SpriteNode* powerShell;
};