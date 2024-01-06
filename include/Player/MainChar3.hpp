#pragma once

#include <MainChar.hpp>
#include <SpriteNode.hpp>

class MainChar3 : public MainChar {
private:
    void updateCurrent(sf::Time dt);

public:
    MainChar3(TextureHolder& textures, CommandQueue& soundCommandQueue, int curLane, std::vector<Lane*>& lanes);
    MainChar3(TextureHolder& textures, sf::Vector2f pos);
    void useAbility();

private:
    int lastHealth;
    
    SpriteNode* powerShell;
    bool isAttach;
    sf::Clock AbilityTime;
    const sf::Time AbilityLength = sf::seconds(5);
};