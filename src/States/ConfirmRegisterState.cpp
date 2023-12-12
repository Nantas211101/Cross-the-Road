#include "ConfirmRegisterState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "GUI_Button.hpp"

ConfirmRegisterState::ConfirmRegisterState(StateStack &stack, Context context)
: State(stack, context)
, mGUIContainer()
, mBackground()
, mText("Register successfully!", context.fonts->get(Fonts::Main), 50)
{
    sf::Vector2f pos = context.window->getView().getCenter();
    mBackground.setFillColor(sf::Color(255, 255, 255, 255));
    mBackground.setSize({context.window->getView().getSize().x / (float)2.5, context.window->getView().getSize().y / (float)2.7});
    mBackground.setOrigin(mBackground.getSize() / 2.f);
    mBackground.setPosition(pos);
    mBackground.setOutlineThickness(15.f);
    mBackground.setOutlineColor(sf::Color(96, 130, 182, 200));


    sf::Font &font = context.fonts->get(Fonts::Main);

    centerOrigin(mText);
    mText.setPosition(pos.x, pos.y - 50.f);
    mText.setFillColor(sf::Color::Black);

    auto returnButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    returnButton->centerOrigin();
    returnButton->setPosition(pos.x - 175.f, pos.y + 100.f);
    returnButton->setScale(0.4, 0.4);
    returnButton->setColor(sf::Color(96, 130, 182, 200));
    returnButton->setText("OK");
    returnButton->setCallback([this](){
        requestStackPop();
        requestStackPop();
        requestStackPush(States::Login);
    });

    auto escapeButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    escapeButton->centerOrigin();
    escapeButton->setPosition(pos.x + 175.f, pos.y + 100.f);
    escapeButton->setScale(0.4, 0.4);
    escapeButton->setColor(sf::Color(96, 130, 182, 200));
    escapeButton->setText("Cancel");
    escapeButton->setCallback([this](){
        requestStackPop();
    });
    
    mGUIContainer.pack(returnButton);
    mGUIContainer.pack(escapeButton);
}

void ConfirmRegisterState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackground);
    window.draw(mText);
    window.draw(mGUIContainer);
}

bool ConfirmRegisterState::update(sf::Time dt){
    return false;
}

bool ConfirmRegisterState::handleEvent(const sf::Event &event){
    handleRealTimeInput();
    mGUIContainer.handleEvent(event);
    if(event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Escape)
            requestStackPop();
        else if(event.key.code == sf::Keyboard::Return){
            requestStackPop();
            requestStackPop();
            requestStackPush(States::Login);
        }
    }
    return false;
}

void ConfirmRegisterState::handleRealTimeInput(){
    sf::RenderWindow &mWindow = *getContext().window;
    mGUIContainer.handleRealTimeInput(mWindow);
}

