#include <River.hpp>
#include <SoundNode.hpp>

River::River(TextureHolder* textureHolder, sf::Vector2f spawnPos, int difficulty, bool reverse)
: Lane(textureHolder, spawnPos, difficulty, reverse){}

unsigned int River::getCategory() const {
    return Category::River;
}

void River::playLocalSound(CommandQueue& commands) {
	sf::Vector2f worldPosition = getWorldPosition();
	SoundEffect::ID effect = SoundEffect::River;
	Command command;
	command.category = Category::SoundEffect;
	command.action = derivedAction<SoundNode>(
		[effect, worldPosition] (SoundNode& node, sf::Time)
		{
			node.playSound(effect, worldPosition);
		});

	commands.push(command);
}

sf::FloatRect River::getBoundingRect() const {
    return getWorldTransform().transformRect(animation.getGlobalBounds());
}