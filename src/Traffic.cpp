#include "Traffic.h"



Traffic::Traffic(const TextureHolder& texture,int status) 
: sprite(texture.get(Textures::Traffic)),sta(status) {
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(0.1f,0.1f);
    if(sta==0){
         sprite.setTextureRect(sf::IntRect(bounds.width/3 * 1, 0, bounds.width/3, bounds.height));
    }else if(sta==1){
        sprite.setTextureRect(sf::IntRect(bounds.width/3 * 2, 0, bounds.width/3, bounds.height));
    }else{
        sprite.setTextureRect(sf::IntRect(bounds.width/3 * 3, 0, bounds.width/3, bounds.height));
    }
}

void Traffic::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Traffic::updateCurrent(sf::Time dt) {
    this->setVelocity(0, 0);
    Entity::updateCurrent(dt);
}

sf::FloatRect Traffic::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

// sf::FloatRect* Traffic::getDangerBound() const {
// 	sf::FloatRect tmp = getBoundingRect();
//     sf::FloatRect* pBound = new sf::FloatRect(tmp);
//     if(type == Traffic::Traffic1) {
//         delete pBound;
//         return nullptr;
//     }
//     tmp.top += 20;
//     tmp.left += 20;
//     tmp.width /= 6;
//     tmp.height /= 1.7;
//     return pBound;
// }