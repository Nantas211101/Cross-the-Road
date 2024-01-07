#include "State.hpp"
#include "StateStack.hpp"
#include <BitMaskingManipulate.hpp>

namespace LVTOMASK{
    const int lvDEST[5] = {1, 4, 6, 11, 16};
    const int maskGET[5] = {Mask(0), Mask(1), Mask(2), Mask(3), Mask(4)};
}

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
                        Player& player, MusicPlayer& music, SoundPlayer& sound, int& Theme,
                        int& limitLevel, int& currentLevel, int& money, std::string& keyMoveUp,
                        std::string& keyMoveDown, std::string& keyMoveLeft, std::string& keyMoveRight,
                        std::string& keyUseAbility, int& currentMusicVolume, int& currentTotalVolume)
: window(&window) // using & because the variable is a pointer (pointer
                    // save address)
, textures(&textures)
, fonts(&fonts)
, player(&player)
, music(&music)
, sounds(&sound)
, theme(&Theme)
, limitLevel(&limitLevel)
, currentLevel(&currentLevel)
, money(&money)
, keyMoveUp(&keyMoveUp)
, keyMoveDown(&keyMoveDown)
, keyMoveLeft(&keyMoveLeft)
, keyMoveRight(&keyMoveRight)
, keyUseAbility(&keyUseAbility)
, currentMusicVolume(&currentMusicVolume)
, currentTotalVolume(&currentTotalVolume)
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

int convertFromLevelToMaskID(int Level)
{
    int res = 0;
    for (int i = 0; i < 5; ++i)
        if (Level >= LVTOMASK::lvDEST[i])
            res |= LVTOMASK::maskGET[i];
    return res;
}