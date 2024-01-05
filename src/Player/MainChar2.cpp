#include <MainChar2.hpp>

MainChar2::MainChar2(TextureHolder& textures, int curLane, std::vector<Lane*>& lanes)
: MainChar(MainChar::Player2, textures, curLane, lanes)
, isAttach(false)
{}

MainChar2::MainChar2(TextureHolder& textures, sf::Vector2f pos)
: MainChar(MainChar::Player2, textures, pos)
{}

void MainChar2::updateCurrent(sf::Time dt) {
    MainChar::updateCurrent(dt);
    sf::Time timeSinceLastAbility = AbilityTime.getElapsedTime();
    if(isAttach && timeSinceLastAbility >= effectLength) {
        heal(healingPoint);
        detachChild(*healingEffect);
        isAttach = false;
        AbilityTime.restart();
    }
    else if(isAttach) {
        mMP = 0;
    }
}

void MainChar2::useAbility() {
    if(canUseAbility()) {
        MainChar::useAbility();
        if(!isAttach) {
            std::unique_ptr<SpriteNode> healing(new SpriteNode(textureHolder.get(Textures::Healing)));
            healingEffect = healing.get();
            attachChild(std::move(healing));
            isAttach = true;
            AbilityTime.restart();
        }
    }
}