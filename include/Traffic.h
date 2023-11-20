#include <SFML/Graphics.hpp>
#include "Entity.h"

#include "TextureHolder.h"

class Traffic: public Entity{
     public:
        Traffic( const TextureHolder& Texture,int status);
        virtual sf::FloatRect getBoundingRect() const;
        sf::FloatRect* getDangerBound() const;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void updateCurrent(sf::Time dt);
 
    private:
        int sta;
        sf::Clock clc;
        sf::Sprite sprite;
};