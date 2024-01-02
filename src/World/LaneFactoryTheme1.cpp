#include <LaneFactoryTheme1.hpp>
LaneFactoryTheme1::LaneFactoryTheme1(TextureHolder* textureHolder, sf::Vector2f startPos, int level) 
: LaneFactory(textureHolder, startPos, level)
{
}

void LaneFactoryTheme1::templateStartLane(int num){
    for(int i = 0; i < num; i++) {
        bool isStart = 1;
        std::unique_ptr<Lane> lane(new GroundTheme1(textureHolder, startPos, GroundTheme1::Grass,isStart, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateFinishTheme(int num){
    std::unique_ptr<Lane> lane(new FinishLane(textureHolder, startPos, level));
    lane->setPosition(startPos);
    startPos.y -= Lane::distanceBetweenLane * 5;
    lanes.push_back(std::move(lane));
}

void LaneFactoryTheme1::templateGround(int num) {
    for(int i = 0; i < num; i++) {
        bool isStart = 0;
        std::unique_ptr<Lane> lane(new GroundTheme1(textureHolder, startPos, GroundTheme1::Grass,isStart, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 1;
        if (num == 1 || i == num - 1) checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme1(textureHolder, startPos, checkLine, RoadTheme1::VehicleRoad, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateAnimalRoad(int num) {
    for(int i = 0; i < num; i++) {
        bool checkLine = 0;
        std::unique_ptr<Lane> lane(new RoadTheme1(textureHolder, startPos, checkLine, RoadTheme1::AnimalRoad, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateRiver(int num) {
    for(int i = 0; i < num; i++) {
        std::unique_ptr<Lane> lane(new RiverTheme1(textureHolder, startPos, level, i%2));
        lane->setPosition(0,startPos.y);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}

void LaneFactoryTheme1::templateRailway(int num) {
    for(int i = 0; i < num; i++) {
        int kind = rand()%2;
        Railway::Type kindTrain;
        switch(kind){
            case 0:
                kindTrain = Railway::WoodTrain;
                break;
            case 1:
                kindTrain = Railway::Train1;
                break;
        }
        std::unique_ptr<Lane> lane(new Railway(textureHolder, startPos, kindTrain, level));
        lane->setPosition(startPos);
        startPos.y -= Lane::distanceBetweenLane;
        lanes.push_back(std::move(lane));
    }
}


void LaneFactoryTheme1::templateLevel1(){
    std::vector<int> templates{1,2,3,4, 5, 10, 6};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1);  
    int randomTemplate;
    for (int i=1; i<=5; i++){
        randomTemplate = dist(gen);
        callTemplateX(templates[randomTemplate]);
    }
}

void LaneFactoryTheme1::templateLevel2(){
    std::vector<int> templates{1,2,3,5, 7, 10, 11, 14};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1);  
    int randomTemplate;
    for (int i=1; i<=7; i++){
        randomTemplate = dist(gen);
        callTemplateX(templates[randomTemplate]);
    }
}

void LaneFactoryTheme1::templateLevel3(){
    std::vector<int> templates{1,2,3,4,5, 6,8, 10, 11, 12,13,14, 15,16,18,20,21};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1);  
    int randomTemplate;
    for (int i=1; i<=9; i++){
        randomTemplate = dist(gen);
        callTemplateX(templates[randomTemplate]);
    }
}

void LaneFactoryTheme1::templateLevel4(){
    std::vector<int> templates{1,2,3,4,5, 6,8, 10, 11, 12,13,14, 15,16,17,18,20,21,24,25};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1); 
    int randomTemplate;
    for (int i=1; i<=14; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}

void LaneFactoryTheme1::templateLevel5(){
    std::vector<int> templates{5,6,8, 10, 11, 12,13,14, 15,16,17,18,20,21,22,23,24,25,26,27,28};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,templates.size()-1);
    int randomTemplate;
    for (int i=1; i<=14; i++){
        randomTemplate = dist(gen);
        callTemplateX(randomTemplate);
    }
}
