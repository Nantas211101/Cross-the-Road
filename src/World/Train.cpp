#include <Train.hpp>
#include <SoundNode.hpp>

namespace {
    const std::vector<TrainData> Table = initializeTrainData();
}

Train::Train(Type type, const TextureHolder& texture) 
: type(type)
, sprite(texture.get(Table[type].texture)) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    //sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(Table[type].scaling);
}

unsigned int Train::getCategory() const {
    return Category::Train;
}

Train::Type Train::getType() {
    return type;
}

void Train::playLocalSound(CommandQueue& commands) {
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

void Train::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Train::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
}

int Train::getDamage(){
    return 75;
}

sf::FloatRect Train::getBoundingRect() const {
    sf::FloatRect bound = getWorldTransform().transformRect(sprite.getGlobalBounds());
    bound.height = std::min(bound.height, (float)Lane::distanceBetweenLane);
    bound.top += 30;
    return bound;
}