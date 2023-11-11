#pragma once

#include "Entity.h"
#include <SFML\Graphics.hpp>

class Lane : public Entity {
    public:
        enum Type {
            Ground,
            Road,
            River,
            TypeCount
        };

    public:
        Lane();
        
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt);

    private:
        Type type;
        int numOfLane;
};