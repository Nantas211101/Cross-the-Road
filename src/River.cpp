#include "../include/River.h"

namespace {
    const std::vector<LaneData> Table = initializeLaneData();
}
// 50: width each lane

void River::loadTexture() {
    textureHolder.load(Textures::Log, "../../Media/Textures/Log.png");
    textureHolder.load(Textures::Eagle, "../../Media/Textures/Eagle.png"); // crocodile
}

River::River(sf::Vector2f spawnPos, const TextureHolder& texture) 
: Lane()
, riverLog()
, timeSinceLastLog(sf::Time::Zero)
, pos(spawnPos) {
    sprite.setTexture(texture.get(Textures::River));
    sf::IntRect textureRect(0, 0, 15000, 50);
    sprite.setTextureRect(textureRect);

    loadTexture();
    buildLog();
}

void River::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void River::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    //timeSinceLastLog += dt;
    // if(timeSinceLastLog >= sf::seconds(5)) {
    //     std::unique_ptr<Log> createLog(new Log(Log::Log1, textureHolder));
    //     riverLog.push_back(createLog.get());
    //     createLog->setPosition(sf::Vector2f(pos.x, pos.y));
    // }
}

void River::buildLog() {
    int speedSameLane = 50 + rand() % 50;
    for(int j = 0; j < 10; j++) {
        std::unique_ptr<Log> log(new Log(Log::Log1, textureHolder));
        riverLog.push_back(log.get());
        if(!this->isReverse())
            log->setVelocity(1.0 * speedSameLane, 0);
        else
            log->setVelocity(-1.0 * speedSameLane, 0);
        int randNum = rand() % 50;
        log->setPosition(pos.x + 300 * j - 4 * randNum, pos.y + 25);
        this->attachChild(std::move(log));
    }
}