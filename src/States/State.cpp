#include "State.hpp"
#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
                        Player& player, MusicPlayer& music, SoundPlayer& sound)
: window(&window) // using & because the variable is a pointer (pointer
                    // save address)
, textures(&textures)
, fonts(&fonts)
, player(&player)
, music(&music)
, sounds(&sound)
{
    
}

State::State(StateStack& stack, Context context)
    : mStack(&stack), mContext(context) {}

State::~State() {} // do not delete mStack
// it is a pointer that not been new in this class

void State::requestStackPush(States::ID stateID) { mStack->pushState(stateID); }

void State::requestStackPop() { mStack->popState(); }

void State::requestStateClear() { mStack->clearStates(); }

auto State::getContext() -> Context const { return mContext; }
