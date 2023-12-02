#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include <assert.h>
#include <map>
#include <vector>

class StateStack : private sf::NonCopyable{
    public:
        enum Action{
            Push,
            Pop,
            Clear,
        };
    
    public:
        explicit StateStack(State::Context context);

        template <typename T>
        void registerState(States::ID stateID);
        
        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event &event);

        // State manipulating with PendingList
        void pushState(States::ID stateID);
        void popState();
        void clearStates();
        auto isEmpty() -> bool const;

    private:
        auto createState(States::ID stateID) -> State::S_Ptr;
        void applyPendingChanges();

    private:
        struct PendingChange{
            explicit    PendingChange(Action action, States::ID stateID = States::None);
            Action      action;
            States::ID  stateID;
        };

    private:
        std::vector<State::S_Ptr>       mStack; // Stack using the vector :)))
        std::vector<PendingChange>      mPendingList; // save the list of waiting action that will be do on the mstack(push, pop, clear)
        State::Context                  mContext; // save the context of the state stack
        std::map<States::ID, std::function<State::S_Ptr()>>    mFactories; // the dictionary of states, save the states
};


// Template
template <typename T>
void StateStack::registerState(States::ID stateID){
    mFactories[stateID] = [this] (){
        return State::S_Ptr(new T(*this, mContext));
    };
}
// Put Template at the same place at include ".inl"