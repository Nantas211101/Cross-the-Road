#pragma once

#include <MainChar.hpp>
#include <SpriteNode.hpp>

class MainChar2 : public MainChar {
private:
    void updateCurrent(sf::Time dt);

public:
    MainChar2(TextureHolder& textures, CommandQueue& soundCommandQueue, int curLane, std::vector<Lane*>& lanes);
    MainChar2(TextureHolder& textures, sf::Vector2f pos);
    void useAbility();

private:
    const int healingPoint = 25;
    
    SpriteNode* healingEffect;
    bool isAttach;
    sf::Clock AbilityTime;
    const sf::Time effectLength = sf::seconds(1);
};