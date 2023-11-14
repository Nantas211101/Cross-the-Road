#include "../include/Grass.h"

void Grass::loadTexture() {
    textureHolder.load(Textures::Tree, "../../Media/Textures/Tree.png");
}

Grass::Grass(const TextureHolder& texture) 
: sprite(texture.get(Textures::Grass))
{}

Grass::Grass(const TextureHolder& texture, const sf::IntRect& textureRect)
: sprite(texture.get(Textures::Grass), textureRect)
{}

Grass::Grass(sf::Vector2f spawnPos, const TextureHolder& texture) 
: Lane()
, Trees()
, timeSinceTree(sf::Time::Zero)
, pos(spawnPos) {
    sprite.setTexture(texture.get(Textures::Grass));
    sf::IntRect textureRect(0, 0, 15000, 50);
    sprite.setTextureRect(textureRect);

    loadTexture();
    buildtree();
}
void Grass::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Grass::updateCurrent(sf::Time dt) {
    // this->setVelocity(0, 0);
    Entity::updateCurrent(dt);
}

void Grass::buildtree() {
    int numTrees = 5 + rand() % 9;
    for(int j = 0; j < numTrees; j++) {
        std::unique_ptr<Tree> tree(new Tree(textureHolder));
        Trees.push_back(tree.get());
        int randNum = rand() % 10;
        tree->setPosition( randNum * 192 + tree->getBoundingRect().width/2 , pos.y );
        this->attachChild(std::move(tree));
    }
}