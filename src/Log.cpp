#include "../include/Log.h"

namespace {
    const std::vector<LogData> Table = initializeLogData();
}

Log::Log(Type type, const TextureHolder& texture) 
: type(type)
, sprite(texture.get(Table[type].texture)) {
    sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(Table[type].scaling);
}

void Log::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Log::updateCurrent(sf::Time dt) {
    this->setVelocity(Table[type].speed, 0);
    Entity::updateCurrent(dt);
}

sf::FloatRect Log::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

sf::FloatRect* Log::getDangerBound() const {
	sf::FloatRect tmp = getBoundingRect();
    sf::FloatRect* pBound = new sf::FloatRect(tmp);
    if(type == Log::Log1) {
        delete pBound;
        return nullptr;
    }
    tmp.top += 20;
    tmp.left += 20;
    tmp.width /= 6;
    tmp.height /= 1.7;
    return pBound;
}