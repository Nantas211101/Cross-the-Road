#include "../include/Game.h"

Game::Game()
: mWindow(sf::VideoMode(640, 480), "Hello")
, mPlayer()
{
    mPlayer.setRadius(40.f);
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen()){
        processEvent();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > timePerFrame){
            timeSinceLastUpdate -= timePerFrame;
            processEvent();
            update(timePerFrame);
        }
        render();
    }
}

void Game::render() {
    mWindow.clear(sf::Color::Black);
    mWindow.draw(mPlayer);
    mWindow.display();
}

// time for process inside
void Game::update(sf::Time elapseTime) {

}

void Game::processEvent() {
    sf::Event event;
    while(mWindow.pollEvent(event)){
        switch(event.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;
            // more event here
        }
    }
}

// processInput
void handleInput() {

}