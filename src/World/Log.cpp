#include "../../include/World/Log.h"

namespace {
    const std::vector<LogData> Table = initializeLogData();
}

Log::Log(Type type, const TextureHolder& texture) 
: type(type)
, sprite(texture.get(Table[type].texture)) {
    sprite.scale(Table[type].scaling);
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
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

sf::FloatRect* Log::getDangerBound() const {
	sf::FloatRect tmp = getBoundingRect();
    sf::FloatRect* pBound = new sf::FloatRect(tmp);
    if(type != Log::Crocodile) {
        delete pBound;
        return nullptr;
    }
    // danger bound of crocodile
    tmp.top += 20;
    tmp.left += 20;
    tmp.width /= 6;
    tmp.height /= 1.7;
    return pBound;
}