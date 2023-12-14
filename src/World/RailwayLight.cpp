#include <RailwayLight.h>

RailwayLight::RailwayLight(const TextureHolder& texture) 
: sprite(texture.get(Textures::RailwayLight)),timeCount(sf::Time::Zero),bounds(sprite.getLocalBounds()) {
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(0.1f,0.1f);
    sprite.setTextureRect(sf::IntRect(bounds.width/2 * sta, 0, bounds.width/2, bounds.height));
}

void RailwayLight::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void RailwayLight::updateCurrent(sf::Time dt) {
  
    timeCount+= dt;

    if(timeCount <= sf::seconds(redTime)){
        sta = 0;
    }else if(timeCount <= sf::seconds(redTime + greenTime)){
        sta = 1;
    }
    else{
        sta = 0;
        timeCount = sf::Time::Zero;
    }
    sprite.setTextureRect(sf::IntRect(bounds.width/2 * sta, 0, bounds.width/2, bounds.height));
}

int RailwayLight::getRailwayLightState(){
    return sta;
}