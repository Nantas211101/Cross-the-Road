#pragma once

#include "Command.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "MainChar.hpp"

#include <SFML/Graphics.hpp>

#include <map>

class CommandQueue;

class Player
{
public:
    enum Action
    {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        ActionCount
    };


public:
                            Player();

    void					handleEvent(const sf::Event& event, CommandQueue& commands);
    void					handleRealtimeInput(CommandQueue& commands);

    void					assignKey(Action action, sf::Keyboard::Key key);
    sf::Keyboard::Key		getAssignedKey(Action action) const;
    void                    setMainCharID(MainChar::Type charID);
    MainChar::Type          getMainCharID();

private:
    void					initializeActions();
    static bool				isRealtimeAction(Action action);


private:
    std::map<sf::Keyboard::Key, Action>		mKeyBinding;
    std::map<Action, Command>				mActionBinding;
    MainChar::Type                          charID;
};
