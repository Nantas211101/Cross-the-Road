#pragma once

#include "../SceneNode.h"
#include <SFML/Graphics.hpp>
#include <ctime>

class Lane : public SceneNode {
    public:
        enum Type {
            Ground,
            Road,
            River,
            Grass,
            TypeCount
        };

    public:
        Lane();
        bool isReverse();
        
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        virtual void updateCurrent(sf::Time dt) = 0;
        virtual void buildLane() = 0;

    private:
        bool reverse;
};