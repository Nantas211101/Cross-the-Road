#include "SFML/Graphics/Rect.hpp"
#include <Vehicle.hpp>
#include <SoundNode.hpp>

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

unsigned int Vehicle::getCategory() const {
    return Category::Vehicle;
}

sf::FloatRect Vehicle::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Vehicle::drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const{
    target.draw(sprite, state);
}

void Vehicle::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
}

int Vehicle::getDamage(){
    return Table[type].dmg;
}

void Vehicle::playLocalSound(CommandQueue &commands) {
	sf::Vector2f worldPosition = getWorldPosition();
	SoundEffect::ID effect = Table[type].collisionEffect;
	Command command;
	command.category = Category::SoundEffect;
	command.action = derivedAction<SoundNode>(
		[effect, worldPosition] (SoundNode& node, sf::Time)
		{
			node.playSound(effect, worldPosition);
		});

	commands.push(command);
}