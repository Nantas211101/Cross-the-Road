#pragma once

#include "Entity.h"
#include "../DataTable.h"
#include "../ResourceIdentifiers.h"
#include "../ResourceHolder.h"
#include "Lane.h"
#include "Tree.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Grass : public Lane {
    public:
        Grass(TextureHolder* textureHolder, sf::Vector2f spawnPos);
    
    private:
        void buildLane();
    
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        bool checkPass(int x,int y);
        bool checkValidPosition(int x,int y);
    
    private:
        int yGrid;
        std::vector<Tree*> Trees;
        sf::Vector2f pos;
        TextureHolder* textureHolder;
        sf::Time timeSinceTree;
        std::vector<std::vector<bool>> ContainTree;
        std::vector<std::vector<bool>> isPass;
;
};