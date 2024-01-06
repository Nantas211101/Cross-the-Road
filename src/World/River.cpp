#include <River.hpp>
#include <SoundNode.hpp>

River::River(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: Lane(textureHolder, spawnPos){}

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