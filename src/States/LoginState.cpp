#include "LoginState.hpp"
#include "Utility.hpp"
#include "TextureManipulate.hpp"
#include "GUI_InputButton.hpp"
#include "GUI_Button.hpp"
#include "GUI_Label.hpp"
#include "GUI_StateButton.hpp"
#include "HashTable.hpp"

#include <fstream>

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

    auto username = std::make_shared<GUI::InputButton>(*context.fonts, *context.textures, "Username");
    username->centerOrigin();
    username->setScale(0.5, 0.5);
    username->setPosition(pos.x, pos.y - 150);
    username->setToggle(true);
    username->setColor(sf::Color(96, 130, 182, 200));
    username->setCallback([this](std::string st){
        mTextUsername = st;
    });

    auto password = std::make_shared<GUI::InputButton>(*context.fonts, *context.textures, "Password");
    password->centerOrigin();
    password->setScale(0.5, 0.5);
    password->setPosition(pos.x, pos.y + 150);
    password->setToggle(true);
    password->setColor(sf::Color(96, 130, 182, 200));
    password->setFlagHidden(true);
    password->setCallback([this](std::string st){
        mTextPassword = st;
    });

    auto registerButton = std::make_shared<GUI::Button>(context);
    registerButton->centerOrigin();
    registerButton->setScale(0.5, 0.5);
    registerButton->setPosition(pos.x - 700.f, pos.y + 351.f);
    registerButton->setText("Register");
    // registerButton->setToggle(true);
    registerButton->setColor(sf::Color(96, 130, 182, 200));
    registerButton->setCallback([this](){
        requestStackPop();
        requestStackPush(States::Register);
    });

    setCenterOrigin(errorText);
    errorText.setPosition(pos.x, pos.y + 300.f);
    errorText.setFillColor(sf::Color::Red);

    auto visibility = std::make_shared<GUI::StateButton>(*context.fonts, *context.textures, Textures::InvisiblePassword, Textures::VisiblePassword);
    visibility->centerOrigin();
    visibility->setPosition(pos.x + 400.f, pos.y + 150.f);
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

    // auto label = std::make_shared<GUI::Label>("", *context.fonts);
    // label->setPosition(pos.x + 400.f, pos.y + 175.5);
    // label->setColor(sf::Color::White);

    auto Login = std::make_shared<GUI::Button>(context);
    Login->centerOrigin();
    Login->setScale(0.5, 0.5);
    Login->setPosition(pos.x + 700.f, pos.y + 351.f);
    Login->setText("Login");
    Login->setColor(sf::Color(96, 130, 182, 200));
    Login->setCallback([this](){
        loginSolver();
        // requestStackPop();
        // requestStackPush(States::ChooseChar);
    });

    mGUIContainer.pack(Login);
    mGUIContainer.pack(registerButton);
    mGUIContainerInputButton.pack(username);
    mGUIContainerInputButton.pack(password);
    mGUIContainerVisibility.pack(visibility);
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
    mGUIContainerInputButton.update(dt);
    return false;
}

bool LoginState::handleEvent(const sf::Event &event)
{
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
    int mask;
    bool ok = 0;
    while(fi >> UID >> username >> passwordHash[0] >> passwordHash[1] >> passwordHash[2] >> passwordHash[3] >> passwordHash[4] >> mask){
        if(username == mTextUsername){
            ok = 1;
            if(checkPassword(mTextPassword, passwordHash)){
                setErrorText("Login success");
                delete [] passwordHash;
                fi.close();
                getContext().player->setMaskID(mask);
                getContext().player->setUID(UID);
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