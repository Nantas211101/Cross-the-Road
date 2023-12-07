#include "../../include/World/Grass.h"

 Grass::Grass(TextureHolder* textureHolder, sf::Vector2f spawnPos)
: Lane()
, textureHolder(textureHolder)
, Trees()
, timeSinceTree(sf::Time::Zero)
, pos(spawnPos) {
    sprite.setTexture(textureHolder->get(Textures::Grass));
    sf::IntRect textureRect(0, 0, 15000, 150);
    sprite.setTextureRect(textureRect);
    
    buildLane();
}
void Grass::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Grass::updateCurrent(sf::Time dt) {
}

// bool Grass::checkPass(int x,int y){

    
//     if(x>=0 && x < ContainTree[0].size() && y >=0 && y < ContainTree.size()&& ContainTree[x][y]==false && isPass[x][y]==false){
//         if(y== ContainTree.size()-1&& ContainTree[x][y]==false) 
//             return true;
//         isPass[x][y]=true;
//         return checkPass(x+1,y)|| checkPass(x,y-1)|| checkPass(x,y+1);
//     }
//     return false;
// }

// bool Grass::checkValidPosition(int x,int y){
//    ContainTree[x][y]=true;
//    for(int i=0 ; i < ContainTree[0].size();i++){
//         if(checkPass(0,i)) return true;
//         for (int k = 0; k < ContainTree.size(); k++) {
//             for (int j = 0; j < ContainTree[k].size(); j++) {
//                 isPass[k][j] = false;
//         }
//     }
//    }
//    ContainTree[x][y]=false;
//    return false;
// }

void Grass::buildLane() {
    int numTrees = 3 + rand() % 2;
    for(int j = 0; j < numTrees; j++) {
        std::unique_ptr<Tree> tree(new Tree(*textureHolder));
        Trees.push_back(tree.get());
        int randNum = rand() % 10;
        // if(j > 0){
        //     while(!checkValidPosition(yGrid,randNum)){
        //      randNum = rand() % 10;
        //     }
        // }
        tree->setPosition( randNum * 192 + tree->getBoundingRect().width/2 , pos.y + 75);
        this->attachChild(std::move(tree));
    }
}

