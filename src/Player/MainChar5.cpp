#include <MainChar5.hpp>

MainChar5::MainChar5(TextureHolder &textures, int curLane, std::vector<Lane*>& lanes)
: MainChar(MainChar::Player5, textures, curLane, lanes)
, isAttach(false)
{}

MainChar5::MainChar5(TextureHolder& textures, sf::Vector2f pos)
: MainChar(MainChar::Player5, textures, pos)
{}

void MainChar5::updateCurrent(sf::Time dt) {
    MainChar::updateCurrent(dt);
    sf::Time timeSinceLastAbility = AbilityTime.getElapsedTime();
    if(isAttach && timeSinceLastAbility >= AbilityLength) {
        detachChild(*powerShell);
        isAttach = false;
        movingVelocity -= accelerateAmount;
        AbilityTime.restart();
    }
    else if(isAttach) {
        mMP = 0;
        mHP = lastHealth;
    }
}

void MainChar5::useAbility() {
    if(canUseAbility()) {
        MainChar::useAbility();

        if(!isAttach) {
            std::unique_ptr<SpriteNode> shell(new SpriteNode(textureHolder.get(Textures::PowerShell)));
            powerShell = shell.get();
            shell->setPosition(-10, -10);
            attachChild(std::move(shell));
            isAttach = true;
        }

        movingVelocity += accelerateAmount;
        lastHealth = getHitpoints();
        AbilityTime.restart();
    }
}