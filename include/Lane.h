#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <ctime>

class Lane : public Entity {
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

    private:
        bool reverse;
};