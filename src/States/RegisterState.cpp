#include "RegisterState.hpp"
#include "Utility.hpp"
#include "TextureManipulate.hpp"
#include "GUI_InputButton.hpp"
#include "GUI_Button.hpp"
#include "GUI_StateButton.hpp"
#include "HashTable.hpp"
#include "StateIdentifiers.hpp"

#include <fstream>

namespace canvaPosition{
    const sf::Vector2f usernamePos = sf::Vector2f(850, 397.5);
    const sf::Vector2f passwordPos = sf::Vector2f(850, 597.5);
    const sf::Vector2f passwordConfirmPos = sf::Vector2f(850, 797.5);
    const sf::Vector2f visibility1ButtonPos = sf::Vector2f(passwordPos.x + 300.f, passwordPos.y);
    const sf::Vector2f visibility2ButtonPos = sf::Vector2f(passwordConfirmPos.x + 300.f, passwordConfirmPos.y);
    const sf::Vector2f registerAcceptButtonPos = sf::Vector2f(1412.5, 816);
    const sf::Vector2f backButtonPos = sf::Vector2f(178.5, 95);
}

const std::pair<int, int> limitUsername = {4, 12};
const std::pair<int, int> limitPassword = {4, 12};

const std::string Main_text = "Register your account";
const std::string Error_Username_Wrong_Size = "Username should be in [" + std::to_string(limitUsername.first) + ", " + std::to_string(limitUsername.second) + ']';
const std::string Error_Password_Wrong_Size = "Password should be in [" + std::to_string(limitPassword.first) + ", " + std::to_string(limitPassword.second) + ']';
const std::string Error_Password_Invalid = "Password should contain at least 1 uppercase\n1 lowercase, 1 Digit and 1 Special Character!";
const std::string Error_Username_Taken = "Username is already taken!\nPlease try again!";
const std::string Error_Password_Not_Match = "Password does not match!\nPlease try again!";

const std::string Error_Information = "Please complete all the information!";

const std::string Path_SaveAccount = "PrivateInfo/AccountSaving.txt";



RegisterState::RegisterState(StateStack &stack, Context context)
: State(stack, context)
, mGUIContainer()
, mGUIContainerVisibility()
, mBackground()
, errorText("", context.fonts->get(Fonts::Main), 50)
, errorTextUsername("", context.fonts->get(Fonts::Main), 30)
, errorTextPassword("", context.fonts->get(Fonts::Main), 30)
, errorTextPasswordConfirm("", context.fonts->get(Fonts::Main), 30)
, mTextUsername()
, mTextPassword()
, mTextPasswordConfirm()
, posErrorUsername()
, posErrorPassword()
, posErrorPasswordConfirm()
, isChangeUsername(false)
, isChangePassword(false)
, isChangePasswordConfirm(false)
, isFocusPassword(true)
, isFocusPasswordConfirm(true)
{
    sf::Vector2f pos = context.window->getView().getCenter();
    mBackground.setTexture(context.textures->get(Textures::RegisterBG));

    auto username = std::make_shared<GUI::InputButton>(*context.fonts, *context.textures, Textures::InputButton,"Username");
    username->centerOrigin();
    username->setPosition(canvaPosition::usernamePos);
    username->setToggle(true);
    username->setCallback([this](std::string st){
        mTextUsername = st;
        isChangeUsername = true;
    });

    posErrorUsername = {canvaPosition::usernamePos.x, canvaPosition::usernamePos.y + 100.f};

    auto password = std::make_shared<GUI::InputButton>(*context.fonts, *context.textures, Textures::InputButton,"Password");
    password->centerOrigin();
    password->setPosition(canvaPosition::passwordPos);
    password->setToggle(true);
    password->setFlagHidden(true);
    password->setCallback([this](std::string st){
        mTextPassword = st;
        isChangePassword = true;
    });

    auto visibility1 = std::make_shared<GUI::StateButton>(*context.fonts, *context.textures, Textures::InvisiblePassword, Textures::VisiblePassword);
    visibility1->centerOrigin();
    visibility1->setPosition(canvaPosition::visibility1ButtonPos);
    visibility1->setCallback([this, password](){
        if(isFocusPassword){
            password->setFlagHidden(false);
            isFocusPassword = false;
        }
        else{
            password->setFlagHidden(true);
            isFocusPassword = true;
        }
    });

    posErrorPassword = {canvaPosition::passwordPos.x, canvaPosition::passwordPos.y + 100.f};

    auto passwordConfirm = std::make_shared<GUI::InputButton>(*context.fonts, *context.textures, Textures::InputButton,"Confirm Password");
    passwordConfirm->centerOrigin();
    passwordConfirm->setPosition(canvaPosition::passwordConfirmPos);
    passwordConfirm->setToggle(true);
    passwordConfirm->setFlagHidden(true);
    passwordConfirm->setCallback([this](std::string st){
        mTextPasswordConfirm = st;
        isChangePasswordConfirm = true;
    });

    auto visibility2 = std::make_shared<GUI::StateButton>(*context.fonts, *context.textures, Textures::InvisiblePassword, Textures::VisiblePassword);
    visibility2->centerOrigin();
    visibility2->setPosition(canvaPosition::visibility2ButtonPos);
    visibility2->setCallback([this, passwordConfirm](){
        if(isFocusPasswordConfirm){
            passwordConfirm->setFlagHidden(false);
            isFocusPasswordConfirm = false;
        }
        else{
            passwordConfirm->setFlagHidden(true);
            isFocusPasswordConfirm = true;
        }
    });

    posErrorPasswordConfirm = {canvaPosition::passwordConfirmPos.x, canvaPosition::passwordConfirmPos.y + 100.f};

    errorText.setFillColor(sf::Color::Red);

    auto registerButton = std::make_shared<GUI::Button>(context, Textures::RegisterAccept);
    registerButton->centerOrigin();
    registerButton->setPosition(canvaPosition::registerAcceptButtonPos);
    registerButton->setScale(0.8f, 0.8f);
    registerButton->setCallback([this](){
        registerAccount();
    });

    auto backButton = std::make_shared<GUI::Button>(context, Textures::BackButton);
    backButton->centerOrigin();
    backButton->setPosition(canvaPosition::backButtonPos);
    backButton->setCallback([this](){
        requestStackPop();
        requestStackPush(States::Login);
    });

    mGUIContainerInputButton.pack(username);
    mGUIContainerInputButton.pack(password);
    mGUIContainerInputButton.pack(passwordConfirm);
    mGUIContainer.pack(registerButton);
    mGUIContainer.pack(backButton);
    mGUIContainerVisibility.pack(visibility1);
    mGUIContainerVisibility.pack(visibility2);

    context.music->play(Music::MenuTheme);
}

void RegisterState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mGUIContainer);
    window.draw(mGUIContainerInputButton);
    window.draw(mGUIContainerVisibility);
    window.draw(errorText);
    window.draw(errorTextUsername);
    window.draw(errorTextPassword);
    window.draw(errorTextPasswordConfirm);
}

bool RegisterState::update(sf::Time dt)
{
    mGUIContainerInputButton.update(dt);
    return false;
}

bool RegisterState::handleEvent(const sf::Event &event)
{
    handleRealTimeInput();
    mGUIContainer.handleEvent(event);
    mGUIContainerInputButton.handleEvent(event);
    mGUIContainerVisibility.handleEvent(event);
    return false;
}

void RegisterState::handleRealTimeInput()
{   
    sf::RenderWindow &mWindow = *getContext().window;
    mGUIContainer.handleRealTimeInput(mWindow);
    mGUIContainerInputButton.handleRealTimeInput(mWindow);
    mGUIContainerVisibility.handleRealTimeInput(mWindow);
    bool isOK = true;
    if(isChangeUsername){
        if(!checkLegalUsername() || !checkUsername())
            isOK = false;
    }
    if(isChangePassword){
        if(!checkLegalPassword())
            isOK = false;
    }
    if(isChangePasswordConfirm){
        if(!checkPassword())
            isOK = false;
    }
    if(isOK)
        setDefaultError();
}

bool RegisterState::checkLegalUsername()
{
    if(mTextUsername.size() < limitUsername.first || mTextUsername.size() > limitUsername.second){
        setErrorUsername(Error_Username_Wrong_Size);
        return false;
    }        
    else 
        setErrorUsername("Valid Username", true);
    return true;
}

bool RegisterState::checkLegalPassword()
{
    if(mTextPassword.size() < limitPassword.first || mTextPassword.size() > limitPassword.second){
        setErrorPassword(Error_Password_Wrong_Size);
        return false;
    }
    else if(!isPasswordValid(mTextPassword)){
        setErrorPassword(Error_Password_Invalid);
        return false;
    }
    else
        setErrorPassword("Valid Password", true);
    return true;
}

bool RegisterState::checkUsername()
{
    std::ifstream fin(Path_SaveAccount);
    if(!fin.is_open()){
        throw std::runtime_error("RegisterState::checkUsername - Cannot open file " + Path_SaveAccount);
        return false;
    }
    int UID;
    std::string username;
    int* passwordHash = new int[5];
    int mask;

    while(fin >> UID >> username >> passwordHash[0] >> passwordHash[1] >> passwordHash[2] >> passwordHash[3] >> passwordHash[4] >> mask){
        if(username == mTextUsername){
            setErrorUsername(Error_Username_Taken);
            fin.close();
            return false;
        }
    }

    setErrorUsername("Valid Username", true);
    fin.close();
    return true;
}

bool RegisterState::checkPassword()
{   
    if(mTextPassword != mTextPasswordConfirm || mTextPasswordConfirm.empty()){
        setErrorPasswordConfirm(Error_Password_Not_Match);
        return false;
    }

    setErrorPasswordConfirm("Valid Password Confirm", true);
    return true;
}

bool RegisterState::isPasswordValid(const std::string& st)
{
    bool isUpper = false, isLower = false, isDigit = false, isSpecial = false;
    for(auto c : st){
        if(c >= 'A' && c <= 'Z')
            isUpper = true;
        else if(c >= 'a' && c <= 'z')
            isLower = true;
        else if(c >= '0' && c <= '9')
            isDigit = true;
        else
            isSpecial = true;
    }
    return isUpper && isLower && isDigit && isSpecial;
}

void RegisterState::setDefaultError(const std::string& st)
{
    // setErrorUsername("");
    // setErrorPassword("");
    // setErrorPasswordConfirm("");
    sf::Vector2f pos = getContext().window->getView().getCenter();
    errorText.setString(st);
    centerOrigin(errorText);
    errorText.setPosition(pos.x, pos.y + 500.f);
}

void RegisterState::setErrorUsername(const std::string& st, bool isValid)
{
    errorTextUsername.setString(st);
    if(isValid)
        errorTextUsername.setFillColor(sf::Color::Green);
    else
        errorTextUsername.setFillColor(sf::Color::Red);
    centerOrigin(errorTextUsername);
    errorTextUsername.setPosition(posErrorUsername);
}

void RegisterState::setErrorPassword(const std::string& st, bool isValid)
{
    errorTextPassword.setString(st);
    if(isValid)
        errorTextPassword.setFillColor(sf::Color::Green);
    else
        errorTextPassword.setFillColor(sf::Color::Red);
    centerOrigin(errorTextPassword);
    errorTextPassword.setPosition(posErrorPassword);
}

void RegisterState::setErrorPasswordConfirm(const std::string& st, bool isValid)
{
    errorTextPasswordConfirm.setString(st);
    if(isValid)
        errorTextPasswordConfirm.setFillColor(sf::Color::Green);
    else
        errorTextPasswordConfirm.setFillColor(sf::Color::Red);
    centerOrigin(errorTextPasswordConfirm);
    errorTextPasswordConfirm.setPosition(posErrorPasswordConfirm);
}

void RegisterState::registerAccount()
{
    // isChangePassword = isChangePasswordConfirm = isChangeUsername = false;
    bool isError = !checkUsername() | !checkLegalPassword() | !checkLegalUsername() | !checkPassword();

    if(isError){
        return;
    }

    std::ofstream fout(Path_SaveAccount, std::ios::app);
    if(!fout.is_open()){
        throw std::runtime_error("RegisterState::registerAccount - Cannot open file output" + Path_SaveAccount);
        return;
    }
    int UID = 0;
    std::string username;
    int* passwordHash = new int[5];
    int mask;

    std::ifstream fin(Path_SaveAccount);
    if(!fin.is_open()){
        throw std::runtime_error("RegisterState::registerAccount - Cannot open file input" + Path_SaveAccount);
        return;
    }

    while(fin >> UID >> username >> passwordHash[0] >> passwordHash[1] >> passwordHash[2] >> passwordHash[3] >> passwordHash[4] >> mask);

    convertStringToHash(mTextPassword, passwordHash);
    fout << UID + 1 << "\n" << mTextUsername << "\n" << passwordHash[0] << " " << passwordHash[1] << " " << passwordHash[2] << " " << passwordHash[3] << " " << passwordHash[4] << "\n" << 1 << "\n";
    
    fout.close();
    fin.close();
    delete [] passwordHash;

    requestStackPush(States::ConfirmRegister);
}