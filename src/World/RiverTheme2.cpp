#include <RiverTheme2.hpp>

namespace {
    const std::vector<LogData> TableLog = initializeLogData();
}

namespace {
    const std::vector<RiverData> TableRiver = initializeRiverData();
}

RiverTheme2::RiverTheme2(TextureHolder* textureHolder, sf::Vector2f spawnPos, int difficulty, bool reverse)
: River(textureHolder, spawnPos, difficulty, reverse)
, riverLog()
{   
    type = River::SnowRiver;
    animation.setTexture(textureHolder->get(TableRiver[type].texture));
    animation.setFrameSize(sf::Vector2i(TableRiver[type].pictureWidth/TableRiver[type].numOfFrames, TableRiver[type].pictureHeight));
	animation.setNumFrames(TableRiver[type].numOfFrames);
	animation.setDuration(sf::seconds(1));
    buildLane();
}

void RiverTheme2::updateCurrent(sf::Time dt) {
    if(!this->isReverse() && riverLog[firstLogIndex]->getPosition().x >= 0) {
        riverLog[lastLogIndex]->setPosition(-TableLog[riverLog[lastLogIndex]->getType()].distanceBetweenLog,25);
        firstLogIndex = lastLogIndex;
        lastLogIndex = (lastLogIndex + numOfLog - 1) % numOfLog;
    }
    if(this->isReverse() && riverLog[lastLogIndex]->getPosition().x <= 2500) {
        riverLog[firstLogIndex]->setPosition(TableLog[riverLog[firstLogIndex]->getType()].distanceBetweenLog + 2500,25);
        lastLogIndex = firstLogIndex;
        firstLogIndex = (firstLogIndex + 1) % numOfLog;
    }
    animation.update(dt);
    animation.setRepeating(true);
}

void RiverTheme2::buildLane() {
    int distance = 0;
    int randomKindLog = rand() % 2;
    Log::Type kind;
    switch(randomKindLog) {
        case 0:
            kind = Log::SnowLog1;
            break;
        case 1:
            kind = Log::SnowLog2;
            break;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist2(minCoefficientRandPos,maxCoefficientRandPos);
    int randSpawnPos = dist2(gen);

    for(int j = 0; j < numOfLog; j++) {
        std::unique_ptr<Log> log(new Log(kind, *textureHolder));
        if(!this->isReverse())
            log->setVelocity(1.0 * TableLog[kind].speed, 0);
        else
            log->setVelocity(-1.0 * TableLog[kind].speed, 0);
        log->setPosition(randSpawnPos*distanceBetweenStartPos + distance,25);
        distance += TableLog[kind].distanceBetweenLog;
        riverLog.push_back(log.get());
        this->attachChild(std::move(log));
    }
    lastLogIndex = numOfLog - 1;
    firstLogIndex = 0;
}

void RiverTheme2::setLaneVelocity(){
    for (auto& it:riverLog){
        it->setVelocity(transformVelocity(it->getVelocity()));
    }
}