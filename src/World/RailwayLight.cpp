#include "../../include/World/RailwayLight.h"

RailwayLight::RailwayLight(const TextureHolder& texture) 
: sprite(texture.get(Textures::Traffic)),timeCount(sf::Time::Zero),bounds(sprite.getLocalBounds()) {
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(0.1f,0.1f);
    sprite.setTextureRect(sf::IntRect(bounds.width/3 * sta, 0, bounds.width/3, bounds.height));
}

void RailwayLight::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void RailwayLight::updateCurrent(sf::Time dt) {
  
    timeCount+= dt;

    if(timeCount <= sf::seconds(redTime)){
        sta = 0;
    }else if(timeCount <= sf::seconds(redTime + greenTime)){
        sta = 2;
    }
    else{
        sta = 0;
        timeCount = sf::Time::Zero;
    }
    sprite.setTextureRect(sf::IntRect(bounds.width/3 * sta, 0, bounds.width/3, bounds.height));
}

int RailwayLight::getRailwayLightState(){
    return sta;
}