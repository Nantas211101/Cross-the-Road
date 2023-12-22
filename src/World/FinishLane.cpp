#include <FinishLane.hpp>

 FinishLane::FinishLane(TextureHolder* textureHolder, sf::Vector2f spawnPos, Type typeFinishLane)
 : Lane(textureHolder, spawnPos)
 , decorators()
 , typeFinishLane(typeFinishLane)
 {
    num = 1;
    switch (this->typeFinishLane){
        case FinishLane::Level:
            sprite.setTexture(textureHolder->get(Textures::FinishLevel));
            num = 3;
            break;
        case FinishLane::Theme1:
            sprite.setTexture(textureHolder->get(Textures::FinishTheme1));
            num = 5;
            break;
        case FinishLane::Theme2:
            sprite.setTexture(textureHolder->get(Textures::FinishTheme2));
            num = 8;
            break;
        case FinishLane::Theme3:
            sprite.setTexture(textureHolder->get(Textures::FinishTheme3));
            num = 7;
            break;
    }
    sf::IntRect textureRect(0, 0, widthOfLane, distanceBetweenLane*num);
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0, bounds.height - distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    buildLane();
 }

 void FinishLane::updateCurrent(sf::Time dt){}

 void FinishLane::buildLane() {
    //create some decorators if need
 }

int FinishLane::getNum(){
    return num;
}