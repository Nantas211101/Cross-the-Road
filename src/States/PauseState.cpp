#include "PauseState.hpp"

#include "ResourceIdentifiers.hpp"
#include "TextureManipulate.hpp"
PauseState::PauseState(StateStack &stack, Context context)
: State(stack, context)
, mBackground()
, mPausedText()
, mInstructionText(){
    // mBackgroundSprite quite useless with PauseState
    sf::Font &font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize(); // get the size of the view


    // create background 
    mBackground.setFillColor(sf::Color(0, 0, 0, 150));
    mBackground.setSize(sf::Vector2f(context.window->getSize()));
    //

    // Init the mPausedText
    mPausedText.setFont(font);
    mPausedText.setString(Paused_text);
    mPausedText.setCharacterSize(70);
    setCenterOrigin(mPausedText);
    mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);
    //

    // Init the mInstructionText
    mInstructionText.setFont(font);
    mInstructionText.setString(Instruction_text);
    setCenterOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
    
    context.music->setPaused(true); // pause the music
}

PauseState::~PauseState()
{
    getContext().music->setPaused(false); // resume the music
}

void PauseState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mPausedText);
    window.draw(mInstructionText);
}

bool PauseState::update(sf::Time dt){
    return false;
}

bool PauseState::handleEvent(const sf::Event &event){
    if(event.type != sf::Event::KeyPressed)
        return false;
    if(event.key.code == sf::Keyboard::Escape){
        requestStackPop(); // pop the PauseState and return to the game
    }
    else if(event.key.code == sf::Keyboard::BackSpace){
        requestStateClear(); 
        // below PauseState only have GameState but GameState may push another State so to be safe we should clear all the state 
        requestStackPush(States::Menu); // and return back to menu state
    }
    else if(event.key.code == sf::Keyboard::Space){
        requestStackPush(States::Settings);
    }
    return false; // why return false at handleEvent and update
    // simply because PauseState will stop all other below state and return false will make the state stack will not touch the below state
}