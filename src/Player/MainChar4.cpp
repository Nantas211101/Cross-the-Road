#include <MainChar4.hpp>

MainChar4::MainChar4(TextureHolder &textures, CommandQueue& soundCommandQueue, int curLane, std::vector<Lane*>& lanes)
: MainChar(MainChar::Player4, textures, soundCommandQueue, curLane, lanes)
, isAttach(false)
{}

MainChar4::MainChar4(TextureHolder& textures, sf::Vector2f pos)
: MainChar(MainChar::Player4, textures, pos)
{}

void MainChar4::updateCurrent(sf::Time dt) {
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
    }
}

void MainChar4::useAbility() {
    if(canUseAbility()) {
        MainChar::useAbility();
        if(!isAttach) {
            std::unique_ptr<SpriteNode> shell(new SpriteNode(textureHolder.get(Textures::PowerShell)));
            powerShell = shell.get();
            shell->setPosition(-5, -10);
            attachChild(std::move(shell));
            isAttach = true;
        }
        movingVelocity += accelerateAmount;
        AbilityTime.restart();
    }
}