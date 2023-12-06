#include "../../include/World/Vehicle.h"

namespace{
    std::vector<VehicleData> Table = initializeVehicleData();  
}

Vehicle::Vehicle(Type type, const TextureHolder& texture)
: type(type)
, sprite(texture.get(Table[type].texture)){
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

Vehicle::Type Vehicle::getType(){
    return type;
}

void Vehicle::drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const{
    target.draw(sprite, state);
}

void Vehicle::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
}