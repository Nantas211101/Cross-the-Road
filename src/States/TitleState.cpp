#include "TitleState.hpp"

TitleState::TitleState(StateStack &stack, Context context)
: State(stack, context)
, mBackgroundSprite()
, mText()
, mDirectorText()
, mProjectText()
, isShowText(true)
, isFocus(true)
, mTextTimeEffected(sf::Time::Zero){
        // context.textures is a pointer so->
    mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

    sf::Vector2f pos = context.window->getView().getSize();

    //
    mText.setFont(context.fonts->get(Fonts::Main));
    mText.setString("Press any key to begin");
    mText.setCharacterSize(75);
    setCenterOrigin(mText);
    mText.setPosition({pos.x / 2.f, pos.y / 2.f + 200.f});
    //

    //
    // mDirectorText.setFont(context.fonts->get(Fonts::Main));
    // mDirectorText.setString("by Vo Truong Thinh - 22125100 - 22TT2");
    // setCenterOrigin(mDirectorText);
    // mDirectorText.setPosition({pos.x / 2.f, pos.y / 2.f - 6 * add_y});
    //

    //
    // mProjectText.setFont(context.fonts->get(Fonts::Main));
    // mProjectText.setString("Star Rail VISUALGO");
    // setCenterOrigin(mProjectText);
    // mProjectText.setScale({2.5, 2.5});
    // mProjectText.setPosition({pos.x / 2.f, pos.y / 2.f - 8 * add_y});
    //
}

bool TitleState::handleEvent(const sf::Event &event){

    switch (event.type)
    {
        case sf::Event::LostFocus:
            isFocus = false;
            return isFocus;
        
        case sf::Event::GainedFocus:
            isFocus = true;
            return isFocus;

        case sf::Event::KeyReleased:
            if(!isFocus) return false;
            requestStackPop(); // pop the title screen
            requestStackPush(States::Menu); // push the menuState screen
            break;

        default:
            if(!isFocus) return false;
            // handleRealTimeInput();
            break;
    }

    // is not focus => dont care about event or realtimeinput
    // if(!isFocus)
    //     return false;

    // if(event.type == sf::Event::KeyReleased){
    //     requestStackPush(States::ChooseChar); // push the menuState screen
    // }
    // else handleRealTimeInput();
    return true;
}

void TitleState::handleRealTimeInput(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        requestStackPop();
        requestStackPush(States::ChooseChar);
    }
}

bool TitleState::update(sf::Time elapsedTime){
    if(!isFocus)
        return false;
    mTextTimeEffected += elapsedTime;

    if(isShowText && mTextTimeEffected >= sf::seconds(0.8f)){
        isShowText = !isShowText; // reverse the state of the text
        mTextTimeEffected = sf::Time::Zero;
    }

    if(!isShowText && mTextTimeEffected >= sf::seconds(0.5f)){
        isShowText = !isShowText; // reverse the state of the text
        mTextTimeEffected = sf::Time::Zero;
    }
    return true;
}

void TitleState::draw(){
    sf::RenderWindow &mWindow = *getContext().window;
    mWindow.draw(mBackgroundSprite);
    
    // mWindow.draw(mProjectText);
    // mWindow.draw(mDirectorText);
    // Make the text blink blink
    if(isShowText)
        mWindow.draw(mText);
}