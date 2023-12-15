#include "StateStack.hpp"

StateStack::StateStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories(){
}

void StateStack::update(sf::Time elapsedTime){
    // Iterate from top to bottom, stop if function return false
    for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr){
        if(!(*itr)->update(elapsedTime))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw(){
    // Draw state from bottom to top
    for(State::S_Ptr &state : mStack)
        state->draw();
}

void StateStack::handleEvent(const sf::Event& event){
    // Iterate from top to bottom, stop if function return false
    for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr){
        if(!(*itr)->handleEvent(event))
            break;
        // if(!(*itr)->handle)
    }

    applyPendingChanges();
}

// State manipulating on PendingList

void StateStack::pushState(States::ID stateID){
    mPendingList.push_back(PendingChange(Push, stateID));
}   

void StateStack::popState(){
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates(){
    mPendingList.push_back(PendingChange(Clear));
}

auto StateStack::isEmpty() -> bool const{
    return mStack.empty();
}

auto StateStack::createState(States::ID stateID) -> State::S_Ptr{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second();
}

void StateStack::applyPendingChanges(){
    for(PendingChange change : mPendingList){
        switch(change.action){
            case Push:
                mStack.push_back(createState(change.stateID));
                break;
            
            case Pop:
                mStack.pop_back();
                break;
            
            case Clear:
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID):
    action(action),
    stateID(stateID){
}