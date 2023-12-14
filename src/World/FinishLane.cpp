#include <FinishLane.hpp>

 FinishLane::FinishLane(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeFinishLane)
 : Lane(textureHolder, spawnPos)
 , decorators()
 , typeFinishLane(typeFinishLane)
 {
    switch (this->typeFinishLane){
        case FinishLane::Level1:
            sprite.setTexture(textureHolder->get(Textures::FinishLevel1));
            break;
        case FinishLane::Level2:
            sprite.setTexture(textureHolder->get(Textures::FinishLevel2));
            break;
        case FinishLane::Level3:
            sprite.setTexture(textureHolder->get(Textures::FinishLevel3));
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
    sf::IntRect textureRect(0, 0, widthOfLane, distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    buildLane();
 }

 void FinishLane::updateCurrent(sf::Time dt){}

 void FinishLane::buildLane() {
    //create some decorators if need
 }
