#include <Obstacle.hpp>
#include <SoundNode.hpp>

namespace{
    std::vector<ObstacleData> Table = initializeObstacleData();  
}

Obstacle::Obstacle(Type type, const TextureHolder& texture) 
: type(type)
, sprite(texture.get(Table[type].texture))
, marked(false) 
{
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(Table[type].scaling);
    sprite.setFrameSize(sf::Vector2i(Table[type].pictureWidth/Table[type].numOfFrames, Table[type].pictureHeight));
	sprite.setNumFrames(Table[type].numOfFrames);
	sprite.setDuration(sf::seconds(1));
}

void Obstacle::playLocalSound(CommandQueue& commands) {
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

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Obstacle::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    sprite.update(dt);
    sprite.setRepeating(true);
}

sf::FloatRect Obstacle::getBoundingRect() const {
    sf::FloatRect bound = getWorldTransform().transformRect(sprite.getGlobalBounds());
    bound.height = std::min(bound.height, (float)Lane::distanceBetweenLane);
    bound.top += Table[type].deltaHeightBound;
    return bound;
}

Obstacle::Type Obstacle::getType() {
    return type;
}

unsigned int Obstacle::getCategory() const {
    if (type == Obstacle::Coin) return Category::Coin;
    return Category::Obstacle;
}

int Obstacle::getDamage() {
    return Table[type].dmg;
}

bool Obstacle::isDestroyed() const {
    return marked;
}

void Obstacle::markedForRemoval() {
    marked = true;
}