#include <LaneFactoryTheme3.hpp>

LaneFactoryTheme3::LaneFactoryTheme3(TextureHolder* textureHolder, sf::Vector2f startPos, int level) 
: LaneFactory(textureHolder, startPos, level)
{}

void LaneFactoryTheme3::templateStartLane(int num){
    for(int i = 0; i < num; i++) {
        bool isStart = 1;
        std::unique_ptr<Lane> lane(new GroundTheme3(textureHolder, startPos, GroundTheme3::Lava,isStart, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateFinishTheme(int num){
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane * 8;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateGround(int num) {
    for(int i = 0; i < num; i++) {
        bool isStart = 0;
        std::unique_ptr<Lane> lane(new GroundTheme3(textureHolder, startPos, GroundTheme3::Lava,isStart, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 1;
        if (num == 1 || i == num - 1) checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme3(textureHolder, startPos, checkLine, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateAnimalRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme3(textureHolder, startPos, checkLine, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateRiver(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new RiverTheme3(textureHolder, startPos, level, i%2));
        lane->setPosition(0,startPos.y);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateRailway(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new Railway(textureHolder, startPos, Railway::LavaTrain, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme3::templateLevel1(){
    std::vector<int> templates{1,2,3,4,5,6,7,8,9,10,17,18,23,24,25,39,40};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1);  
    int randomTemplate;
    for (int i=1; i<=11; i++){
        randomTemplate = dist(gen);
        callTemplateX(templates[randomTemplate]);
    }
}

void LaneFactoryTheme3::templateLevel2(){
    std::vector<int> templates{1,2,4,5,6,7,8,9,10,11,12,15,16,18,23,24,25,26,27,31,32,36,37,40};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1);  
    int randomTemplate;
    for (int i=1; i<=13; i++){
        randomTemplate = dist(gen);
        callTemplateX(templates[randomTemplate]);
    }
}

void LaneFactoryTheme3::templateLevel3(){
    std::vector<int> templates{4,5,6,7,8,9,10,11,12,15,16,17,18,20,23,24,25,26,28,29,31,33,34,35,36,37,38,39,40,33,34,35,33,34};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1);  
    int randomTemplate;
    for (int i=1; i<=15; i++){
        randomTemplate = dist(gen);
        callTemplateX(templates[randomTemplate]);
    }
}

void LaneFactoryTheme3::templateLevel4(){
    std::vector<int> templates{4,5,6,7,8,9,10,11,12,13,15,16,17,18,19,20,21,22,23,24,25,26,28,29,30,31,32,33,34,35,36,37,38,39,40,39,40,36,37,33,34,35,33,34,35,33};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1); 
    int randomTemplate;
    for (int i=1; i<=17; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme3::templateLevel5(){
    std::vector<int> templates{5,6,7,8,9,10,11,12,13,15,16,17,18,19,20,21,22,23,24,25,26,28,29,30,31,32,33,34,35,36,37,38,39,40,36,37,38,39,40,39,40,33,34,35,33,34,35,33};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1);
    int randomTemplate;
    for (int i=1; i<=22; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}
