#pragma once
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "GUI_Container.hpp"
#include "GUI_ContainerSET.hpp"
#include "ResourceHolder.hpp"

#include <string>

class RegisterState : public State{
public: 
    RegisterState(StateStack &stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);

private:
    virtual void handleRealTimeInput();
    bool checkLegalUsername();
    bool checkLegalPassword();
    bool checkUsername();
    bool checkPassword();

    bool isPasswordValid(const std::string& st);

    void setDefaultError(const std::string& st = "");
    void setErrorUsername(const std::string& st, bool isValid = false);
    void setErrorPassword(const std::string& st, bool isValid = false);
    void setErrorPasswordConfirm(const std::string& st, bool isValid = false);

    void registerAccount();

private:
    GUI::Container mGUIContainer;
    GUI::Container mGUIContainerInputButton;
    GUI::Container mGUIContainerVisibility;
    sf::Sprite mBackground;

    sf::Text errorText;
    sf::Text errorTextUsername;
    sf::Text errorTextPassword;
    sf::Text errorTextPasswordConfirm;
    std::string mTextUsername;
    std::string mTextPassword;
    std::string mTextPasswordConfirm;

    sf::Vector2f posErrorUsername;
    sf::Vector2f posErrorPassword;
    sf::Vector2f posErrorPasswordConfirm;

    bool isChangeUsername;
    bool isChangePassword;
    bool isChangePasswordConfirm;

    bool isFocusPassword;
    bool isFocusPasswordConfirm;

    sf::Time mElapsedTime;
};