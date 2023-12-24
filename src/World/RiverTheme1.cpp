#include <RiverTheme1.hpp>

namespace {
    const std::vector<LogData> TableLog = initializeLogData();
}

namespace {
    const std::vector<RiverData> TableRiver = initializeRiverData();
}

RiverTheme1::RiverTheme1(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: River(textureHolder, spawnPos)
, riverLog()
{   
    type = River::WaterRiver;
    animation.setTexture(textureHolder->get(TableRiver[type].texture));
    animation.setFrameSize(sf::Vector2i(TableRiver[type].pictureWidth/TableRiver[type].numOfFrames, TableRiver[type].pictureHeight));
	animation.setNumFrames(TableRiver[type].numOfFrames);
	animation.setDuration(sf::seconds(1.5));
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
    animation.update(dt);
    animation.setRepeating(true);
}

void RiverTheme1::buildLane() {
    int distance = 0;
    int randomKindLog = 1 + rand() % 2;
    Log::Type kind;
    switch(randomKindLog) {
    case 1:
        kind = Log::Log1;
        break;
    case 2:
        kind = Log::Log2;
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