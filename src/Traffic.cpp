#include "Traffic.h"



Traffic::Traffic(const TextureHolder& texture,int status) 
: sprite(texture.get(Textures::Traffic)),sta(status),timeCount(sf::Time::Zero),bounds(sprite.getLocalBounds()) {
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(0.1f,0.1f);
    sprite.setTextureRect(sf::IntRect(bounds.width/3 * sta, 0, bounds.width/3, bounds.height));
}

void Traffic::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Traffic::updateCurrent(sf::Time dt) {
  
    timeCount+= dt;

    if(timeCount <= sf::seconds(redTime)){
        sta = 0;
    }else if(timeCount <= sf::seconds(redTime + greenTime)){
        sta = 2;
    }else if(timeCount <= sf::seconds(redTime + yellowTime + greenTime)){
        sta = 1;
    }else{
        sta = 0;
        timeCount = sf::Time::Zero;
    }
    sprite.setTextureRect(sf::IntRect(bounds.width/3 * sta, 0, bounds.width/3, bounds.height));
}

int Traffic::getTrafficState(){
    return sta;
}