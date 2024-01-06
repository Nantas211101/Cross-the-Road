#include "LoginState.hpp"
#include "Utility.hpp"
#include "TextureManipulate.hpp"
#include "GUI_InputButton.hpp"
#include "GUI_Button.hpp"
#include "GUI_Label.hpp"
#include "GUI_StateButton.hpp"
#include "HashTable.hpp"

#include <fstream>

// namespace lvOpen{
//     const int lvOpenChar[]
// }
namespace canvaPosition{
    const sf::Vector2f usernamePos = sf::Vector2f(850, 435);
    const sf::Vector2f passwordPos = sf::Vector2f(850, 608);
    const sf::Vector2f visibilityButtonPos = sf::Vector2f(passwordPos.x + 300.f, passwordPos.y);
    const sf::Vector2f loginButtonPos = sf::Vector2f(1412.5, 816);
    const sf::Vector2f registerButtonPos = sf::Vector2f(220, 816);
}

const std::string Error_Wrong_Information = "Wrong username or password!\n Please try again!";
const std::string Error_Account_Not_Exist = "Account does not exist!\n Please try again!";
const std::string Error_Not_Fill_Enough = "Please fill in all the information!";

const std::string Path_SaveAccount = "PrivateInfo/AccountSaving.txt";

LoginState::LoginState(StateStack &stack, Context context)
: State(stack, context)
, mGUIContainer()
, mGUIContainerVisibility()
, mBackground()
, errorText("", context.fonts->get(Fonts::Main), 50)
, mTextUsername()
, mTextPassword()
, isFocus(true)
{
    sf::Vector2f pos = context.window->getView().getCenter();
    mBackground.setTexture(context.textures->get(Textures::LoginBG));
    mBackground.setPosition(0, 0);

    auto username = std::make_shared<GUI::InputButton>(*context.fonts, *context.textures, Textures::InputButton, "Username");
    username->centerOrigin();
    username->setPosition(canvaPosition::usernamePos);
    username->setToggle(true);
    // username->setColor(sf::Color(96, 130, 182, 200));
    username->setCallback([this](std::string st){
        mTextUsername = st;
    });

    auto password = std::make_shared<GUI::InputButton>(*context.fonts, *context.textures, Textures::InputButton,"Password");
    password->centerOrigin();
    password->setPosition(canvaPosition::passwordPos);
    password->setToggle(true);
    // password->setColor(sf::Color(96, 130, 182, 200));
    password->setFlagHidden(true);
    password->setCallback([this](std::string st){
        mTextPassword = st;
    });

    auto registerButton = std::make_shared<GUI::Button>(context, Textures::RegisterButton);
    registerButton->centerOrigin();
    registerButton->setPosition(canvaPosition::registerButtonPos);
    registerButton->setCallback([this](){
        requestStackPop();
        requestStackPush(States::Register);
    });

    setCenterOrigin(errorText);
    errorText.setPosition(pos.x, pos.y + 200.f);
    errorText.setFillColor(sf::Color::Red);

    auto visibility = std::make_shared<GUI::StateButton>(*context.fonts, *context.textures, Textures::InvisiblePassword, Textures::VisiblePassword);
    visibility->centerOrigin();
    visibility->setPosition(canvaPosition::visibilityButtonPos);
    visibility->setColor(sf::Color(96, 130, 182, 200)); 
    visibility->setCallback([this, password](){
        if(isFocus){
            password->setFlagHidden(false);
            isFocus = false;
        }
        else{
            password->setFlagHidden(true);
            isFocus = true;
        }
    });

    auto Login = std::make_shared<GUI::Button>(context, Textures::LoginButton);
    Login->centerOrigin();
    Login->setPosition(canvaPosition::loginButtonPos);
    Login->setScale(0.8f, 0.8f);
    // Login->setFlagSelection(false);
    // Login->setColor(sf::Color(96, 130, 182, 200));
    Login->setCallback([this](){
        loginSolver();
    });

    mGUIContainer.pack(Login);
    mGUIContainer.pack(registerButton);
    mGUIContainerInputButton.pack(username);
    mGUIContainerInputButton.pack(password);
    mGUIContainerVisibility.pack(visibility);
    
    context.music->play(Music::MenuTheme);
}

void LoginState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());


    window.draw(mBackground);
    window.draw(mGUIContainer);
    window.draw(mGUIContainerInputButton);
    window.draw(mGUIContainerVisibility);
    window.draw(errorText);
}

bool LoginState::update(sf::Time dt)
{
    mElapsedTime += dt;
    mGUIContainerInputButton.update(dt);
    return false;
}

bool LoginState::handleEvent(const sf::Event &event)
{
    if(mElapsedTime < sf::seconds(1.0))
        return false;
    handleRealTimeInput();
    mGUIContainer.handleEvent(event);
    mGUIContainerInputButton.handleEvent(event);
    mGUIContainerVisibility.handleEvent(event);
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
        loginSolver();
    }
    return false;
}

void LoginState::handleRealTimeInput()
{
    sf::RenderWindow &mWindow = *getContext().window;
    mGUIContainer.handleRealTimeInput(mWindow);
    mGUIContainerInputButton.handleRealTimeInput(mWindow);
    mGUIContainerVisibility.handleRealTimeInput(mWindow);
}

void LoginState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    return;
}

bool LoginState::hashCheck(std::string password, int* passwordHash)
{
    return 1;
}

void LoginState::setErrorText(std::string error)
{
    sf::Vector2f pos = errorText.getPosition();
    errorText.setString(error);
    setCenterOrigin(errorText);
    errorText.setPosition(pos);
}

void LoginState::loginSolver()
{
    if (mTextUsername.empty() || mTextPassword.empty()){
        setErrorText(Error_Not_Fill_Enough);
        return;
    }
    std::ifstream fi(Path_SaveAccount);
    if(!fi.is_open()){
        throw std::runtime_error("RegisterState::loginSolver - Cannot open file " + Path_SaveAccount);
        return;
    }
    int UID;
    std::string username;
    int* passwordHash = new int[5];
    int lv;
    bool ok = 0;
    while(fi >> UID >> username >> passwordHash[0] >> passwordHash[1] >> passwordHash[2] >> passwordHash[3] >> passwordHash[4] >> lv){
        if(username == mTextUsername){
            ok = 1;
            if(checkPassword(mTextPassword, passwordHash)){
                setErrorText("Login success");
                delete [] passwordHash;
                fi.close();
                getContext().player->setMaskID(convertFromLevelToMaskID(lv));
                getContext().player->setUID(UID);
                *getContext().limitLevel = lv;
                requestStackPop();
                requestStackPush(States::Menu);
                // Login success
                return;
            }
            else{
                // Wrong password
                setErrorText(Error_Wrong_Information);
                delete [] passwordHash;
                fi.close();
                return;
            }
        }
    }

    if(!ok)
        setErrorText(Error_Account_Not_Exist);

    delete [] passwordHash;
    fi.close();
    return;
}