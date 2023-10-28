#pragma once
#include <SFML/Graphics.hpp>

class Game {
    private:
        const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
        sf::RenderWindow mWindow;
        sf::CircleShape mPlayer;
    private:
        void processEvent();
        void update(sf::Time elapseTime);
        void render();
        void handleInput();
    public:
        Game();
        void run();
};