#pragma once

#include "Entity.h"
#include "DataTable.h"
#include "TextureHolder.h"
#include "Lane.h"
#include "SpriteNode.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tree.h"

class Grass : public Lane {
    public:
        Grass(const TextureHolder& texture);
        Grass(const TextureHolder& texture, const sf::IntRect& textureRect);
        Grass(sf::Vector2f spawnPos, const TextureHolder& texture);
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
        void buildtree();
        void loadTexture();
    private:
        sf::Sprite sprite;
        std::vector<Tree*> Trees;
        sf::Vector2f pos;
        TextureHolder textureHolder;
        sf::Time timeSinceTree;
};