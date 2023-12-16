#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateStack.hpp"

const std::string Paused_text = "World Stopbu";
const std::string Instruction_text = "(Press Backspace to return to the menu)\n(Press Escape to return to the game)\n(Press Space to turn on settings)";

class PauseState : public State{
    public:
        PauseState(StateStack &stack, Context context);
        ~PauseState();
        
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event &event);

    private:
        sf::RectangleShape mBackground;
        sf::Text mPausedText;
        sf::Text mInstructionText;
};
