#include <MainChar3.hpp>

MainChar3::MainChar3(TextureHolder &textures, int curLane, std::vector<Lane*>& lanes)
: MainChar(MainChar::Player3, textures, curLane, lanes)
, isAttach(false)
{}

MainChar3::MainChar3(TextureHolder& textures, sf::Vector2f pos)
: MainChar(MainChar::Player3, textures, pos)
{}

void MainChar3::updateCurrent(sf::Time dt) {
    MainChar::updateCurrent(dt);
    sf::Time timeSinceLastAbility = AbilityTime.getElapsedTime();
    if(isAttach && timeSinceLastAbility >= AbilityLength) {
        detachChild(*powerShell);
        isAttach = false;
        AbilityTime.restart();
    }
    else if(isAttach) {
        mMP = 0;
        mHP = lastHealth;
    }
}

void MainChar3::useAbility() {
    if(canUseAbility()) {
        MainChar::useAbility();
        if(!isAttach) {
            std::unique_ptr<SpriteNode> shell(new SpriteNode(textureHolder.get(Textures::PowerShell)));
            powerShell = shell.get();
            shell->setPosition(-5, -10);
            attachChild(std::move(shell));
            isAttach = true;
        }
        lastHealth = getHitpoints();
        AbilityTime.restart();
    }
}