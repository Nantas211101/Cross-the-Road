#include <Log.hpp>

namespace {
    const std::vector<LogData> Table = initializeLogData();
}

Log::Log(Type type, const TextureHolder& texture) 
: type(type)
, sprite(texture.get(Table[type].texture)) {
    sprite.scale(Table[type].scaling);
}

unsigned int Log::getCategory() const {
    return Category::Log;
}

Log::Type Log::getType() {
    return type;
}

void Log::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Log::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
}

sf::FloatRect Log::getBoundingRect() const {
    sf::FloatRect bound = getWorldTransform().transformRect(sprite.getGlobalBounds());
    bound.height = (float)Lane::distanceBetweenLane;
    bound.top -= 25;
    bound.left += Table[type].deltaLeftBound;
    bound.width -= Table[type].deltaWidthBound;
    return bound;
}