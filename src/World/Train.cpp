#include <Train.hpp>
#include <SoundNode.hpp>

namespace {
    const std::vector<TrainData> Table = initializeTrainData();
}

Train::Train(Type type, const TextureHolder& texture) 
: type(type)
, sprite(texture.get(Table[type].texture)) {
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

sf::FloatRect Train::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}