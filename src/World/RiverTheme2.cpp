#include "../../include/World/RiverTheme2.h"

RiverTheme2::RiverTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: River(textureHolder, spawnPos)
, riverLog()
{
    textureHolder->get(Textures::LavaRiver).setRepeated(true);
    sprite.setTexture(textureHolder->get(Textures::LavaRiver));
    sf::IntRect textureRect(0, 0, 3000, distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    buildLane();
}

unsigned int RiverTheme2::getCategory() const {
    return Category::River;
}

sf::FloatRect RiverTheme2::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void RiverTheme2::updateCurrent(sf::Time dt) {
    if(!this->isReverse() && riverLog[firstLogIndex]->getPosition().x >= 0) {
        riverLog[lastLogIndex]->setPosition(-TableLog[riverLog[lastLogIndex]->getType()].distanceBetweenLog, startPos.y + 25);
        firstLogIndex = lastLogIndex;
        lastLogIndex = (lastLogIndex + numOfLog - 1) % numOfLog;
    }
    if(this->isReverse() && riverLog[lastLogIndex]->getPosition().x <= 2500) {
        riverLog[firstLogIndex]->setPosition(TableLog[riverLog[firstLogIndex]->getType()].distanceBetweenLog + 2500, startPos.y + 25);
        lastLogIndex = firstLogIndex;
        firstLogIndex = (firstLogIndex + 1) % numOfLog;
    }
}

void RiverTheme2::buildLane() {
    int distance = 0;
    int randomKindLog = 1 + rand() % 3;
    Log::Type kind;
    switch(randomKindLog) {
    case 1:
        kind = Log::Log1;
        break;
    case 2:
        kind = Log::Log2;
        break;
    case 3:
        kind = Log::Log3;
        break;
    }
    int randSpawnPos = rand() % 200;
    for(int j = 0; j < numOfLog; j++) {
        std::unique_ptr<Log> log(new Log(kind, *textureHolder));
        if(!this->isReverse())
            log->setVelocity(1.0 * TableLog[kind].speed, 0);
        else
            log->setVelocity(-1.0 * TableLog[kind].speed, 0);
        log->setPosition(startPos.x + randSpawnPos + distance, startPos.y + 25);
        distance += TableLog[kind].distanceBetweenLog;
        riverLog.push_back(log.get());
        this->attachChild(std::move(log));
    }
    lastLogIndex = numOfLog - 1;
    firstLogIndex = 0;
}