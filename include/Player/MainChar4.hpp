#pragma once

#include <MainChar.hpp>
#include <SpriteNode.hpp>

class MainChar4 : public MainChar {
private:
    void updateCurrent(sf::Time dt);

public:
    MainChar4(TextureHolder& textures, int curLane, std::vector<Lane*>& lanes);
    MainChar4(TextureHolder& textures, sf::Vector2f pos);
    void useAbility();

private:
    const int accelerateAmount = 100;
    
    SpriteNode* powerShell;
    bool isAttach;
    sf::Clock AbilityTime;
    const sf::Time AbilityLength = sf::seconds(5);
};