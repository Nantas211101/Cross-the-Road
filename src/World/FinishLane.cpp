#include <FinishLane.h>

 FinishLane::FinishLane(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeFinishLane)
 : Lane(textureHolder, spawnPos)
 , decorators()
 , typeFinishLane(typeFinishLane)
 {
    switch (this->typeFinishLane){
        case FinishLane::Level:
            textureHolder->get(Textures::FinishLevel).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::FinishLevel));
            break;
        case FinishLane::Theme1:
            textureHolder->get(Textures::FinishTheme1).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::FinishTheme1));
            break;
        case FinishLane::Theme2:
            textureHolder->get(Textures::FinishTheme2).setRepeated(true);
            sprite.setTexture(textureHolder->get(Textures::FinishTheme2));
            break;
    }
    sf::IntRect textureRect(0, 0, 15000, distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    buildLane();
 }

 void FinishLane::updateCurrent(sf::Time dt){}

 void FinishLane::buildLane() {
    //create some decorators if need
 }
