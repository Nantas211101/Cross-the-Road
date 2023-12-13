#include <RiverTheme1.h>

RiverTheme1::RiverTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: River(textureHolder, spawnPos)
, riverLog()
{
    textureHolder->get(Textures::River).setRepeated(true);
    sprite.setTexture(textureHolder->get(Textures::River));
    sf::IntRect textureRect(0, 0, 3000, distanceBetweenLane);
    sprite.setTextureRect(textureRect);
    buildLane();
}

void RiverTheme1::updateCurrent(sf::Time dt) {
    if(!this->isReverse() && riverLog[firstLogIndex]->getPosition().x >= 0) {
        riverLog[lastLogIndex]->setPosition(-TableLog[riverLog[lastLogIndex]->getType()].distanceBetweenLog, 25);
        firstLogIndex = lastLogIndex;
        lastLogIndex = (lastLogIndex + numOfLog - 1) % numOfLog;
    }
    if(this->isReverse() && riverLog[lastLogIndex]->getPosition().x <= 2500) {
        riverLog[firstLogIndex]->setPosition(TableLog[riverLog[firstLogIndex]->getType()].distanceBetweenLog + 2500, 25);
        lastLogIndex = firstLogIndex;
        firstLogIndex = (firstLogIndex + 1) % numOfLog;
    }
}

void RiverTheme1::buildLane() {
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
        log->setPosition(randSpawnPos + distance, 25);
        distance += TableLog[kind].distanceBetweenLog;
        riverLog.push_back(log.get());
        this->attachChild(std::move(log));
    }
    lastLogIndex = numOfLog - 1;
    firstLogIndex = 0;
}