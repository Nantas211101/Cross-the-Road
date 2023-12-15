#pragma once
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "GUI_Container.hpp"
#include "GUI_ContainerSET.hpp"
#include "ResourceHolder.hpp"

#include <string>

class LoginState : public State{
public:
    LoginState(StateStack &stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);
    virtual void handleRealTimeInput();

private: 
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void loginSolver();
    bool hashCheck(std::string password, int* passwordHash);
    void setErrorText(std::string error);

private:
    GUI::Container mGUIContainer;
    GUI::Container mGUIContainerInputButton;
    GUI::Container mGUIContainerVisibility;
    
    sf::Sprite mBackground;

    sf::Text mText;
    sf::Text errorText;
    std::string mTextUsername;
    std::string mTextPassword;
    // sf::Text mTextLogin;
    // sf::Text mTextRegister;
    // sf::Text mTextError;
    
    bool isFocus;


};
