#include <Player3.hpp>

Player3::Player3(TextureHolder &textures, int curLane, std::vector<Lane*>& lanes)
: MainChar(MainChar::Player3, textures, curLane, lanes)
, textureHolder(textures)
, abilityActive(false)
, isAttach(true)
{
    std::unique_ptr<SpriteNode> shell(new SpriteNode(textures.get(Textures::PowerShell)));
    powerShell = shell.get();
    shell->setPosition(-15, -15);
    attachChild(std::move(shell));
}

Player3::Player3(TextureHolder& textures, sf::Vector2f pos)
: MainChar(MainChar::Player3, textures, pos)
, textureHolder(textures)
, abilityActive(false)
{}

void Player3::updateCurrent(sf::Time dt) {
    MainChar::updateCurrent(dt);
    sf::Time timeSinceLastAbility = AbilityTime.getElapsedTime();
    if(abilityActive == true) {
        mMP = 0;
        mHP = lastHealth;
        if(!isAttach) {
            std::unique_ptr<SpriteNode> shell(new SpriteNode(textureHolder.get(Textures::PowerShell)));
            powerShell = shell.get();
            shell->setPosition(-15, -15);
            attachChild(std::move(shell));
            isAttach = true;
        }
    }
    else if(abilityActive == false) {
        if(isAttach) {
            detachChild(*powerShell);
            isAttach = false;
        }
    }
    if(abilityActive == true && timeSinceLastAbility >= AbilityLength) {
        abilityActive = false;
        AbilityTime.restart();
    }
}

void Player3::useAbility() {
    if(canUseAbility()) {
        MainChar::useAbility();
        abilityActive = true;
        lastHealth = getHitpoints();
        AbilityTime.restart();
    }
}