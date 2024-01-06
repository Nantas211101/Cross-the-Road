#include <CreditsState.hpp>
#include <Utility.hpp>
#include <string>
#include <math.h>

const sf::Vector2f viewSpeed = sf::Vector2f(0.f, 150.f);

// const std::string creditText = std::string("Cross-The-Road\n\n")
// + std::string("Developed by:\n")
// + std::string("Vo Truong Thinh - 22125100\n")
// + std::string("Dao Xuan Thanh - 22125095\n")
// + std::string("Vo Nhu Thien - 22125097\n")
// + std::string("Tran Thanh Tien - 22125105\n\n")

// + std::string("Directed by:\n")
// + std::string("Dao Xuan Thanh\n\n")

// + std::string("Story Idea:\n")
// + std::string("Vo Truong Thinh\n\n")

// + std::string("Designed by:\n")
// + std::string("Tran Thanh Tien\n")
// + std::string("Dao Xuan Thanh\n\n")

// + std::string("Editor:\n")
// + std::string("Vo Nhu Thien\n\n")

// + std::string("Music:\n")
// + std::string("LittleRoot Town - Pokemon Ruby/Sapphire/Emerald\n")
// + std::string("Pokemon Center - Pokemon: Ruby and Sapphire\n")

// + std::string("Special Thanks:\n")
// + std::string("pngtree.com\n")
// + std::string("gamemaker.io\n\n")

// + std::string("Thanks for playing!");

const float add_y = 100;

CreditsState::CreditsState(StateStack& stack, Context context)
: State(stack, context)
// , mBackground()
, mWorldView(context.window->getDefaultView())
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y + 2000.f)
// , mText(creditText, context.fonts->get(Fonts::Label), 75)
, mTexts()
, mText("Thanks for playing!", context.fonts->get(Fonts::Label), 100)
, mInstructionText("Press ESC to return to menu", context.fonts->get(Fonts::Label), 25)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y * 1)
, mElapsedTime(sf::Time::Zero)
{
    int cnt = 0;
    setNewText("Cross-The-Road", cnt, context.fonts->get(Fonts::Label), 75);
    cnt += 2;
    setNewText("Developed by:", cnt, context.fonts->get(Fonts::Label), 60);
    ++cnt;
    setNewText("Vo Truong Thinh - 22125100", cnt, context.fonts->get(Fonts::Label), 50);
    ++cnt;
    setNewText("Dao Xuan Thanh - 22125095", cnt, context.fonts->get(Fonts::Label), 50);
    ++cnt;
    setNewText("Vo Nhu Thien - 22125097", cnt, context.fonts->get(Fonts::Label), 50);
    ++cnt;
    setNewText("Tran Thanh Tien - 22125105", cnt, context.fonts->get(Fonts::Label), 50);
    cnt += 2;
    setNewText("Directed by:", cnt, context.fonts->get(Fonts::Label), 60);
    ++cnt;
    setNewText("Dao Xuan Thanh", cnt, context.fonts->get(Fonts::Label), 50);
    cnt += 2;
    setNewText("Story Idea:", cnt, context.fonts->get(Fonts::Label), 60);
    ++cnt;
    setNewText("Vo Truong Thinh", cnt, context.fonts->get(Fonts::Label), 50);
    cnt += 2;
    setNewText("Designed by:", cnt, context.fonts->get(Fonts::Label), 60);
    ++cnt;
    setNewText("Tran Thanh Tien", cnt, context.fonts->get(Fonts::Label), 50);
    ++cnt;
    setNewText("Dao Xuan Thanh", cnt, context.fonts->get(Fonts::Label), 50);
    cnt += 2;
    setNewText("Editor:", cnt, context.fonts->get(Fonts::Label), 60);
    ++cnt;
    setNewText("Vo Nhu Thien", cnt, context.fonts->get(Fonts::Label), 50);
    cnt += 2;
    setNewText("Music:", cnt, context.fonts->get(Fonts::Label), 60);
    ++cnt;
    setNewText("LittleRoot Town - Pokemon Ruby/Sapphire/Emerald", cnt, context.fonts->get(Fonts::Label), 50);
    ++cnt;
    setNewText("Pokemon Center - Pokemon: Ruby and Sapphire", cnt, context.fonts->get(Fonts::Label), 50);
    cnt += 2;
    setNewText("Special Thanks:", cnt, context.fonts->get(Fonts::Label), 60);
    ++cnt;
    setNewText("pngtree.com", cnt, context.fonts->get(Fonts::Label), 50);
    ++cnt;
    setNewText("gamemaker.io", cnt, context.fonts->get(Fonts::Label), 50);
    
    mText.setFillColor(sf::Color::White);
    centerOrigin(mText);
    mText.setPosition(mSpawnPosition + sf::Vector2f(0.f, cnt * add_y) + sf::Vector2f(0.f, mWorldView.getSize().y));

    mInstructionText.setFillColor(sf::Color(255, 255, 255, 0));
    centerOrigin(mInstructionText);
    mInstructionText.setPosition(mSpawnPosition + sf::Vector2f(0.f, cnt * add_y) + sf::Vector2f(0.f, mWorldView.getSize().y) + sf::Vector2f(0.f, 100.f));

    mWorldView.setCenter(mSpawnPosition.x, mWorldView.getSize().y / 3.f);

    context.music->play(Music::CreditsTheme);
}

void CreditsState::draw(){
    sf::RenderWindow &window = *getContext().window;
    window.setView(mWorldView);

    for(auto& text: mTexts)
        window.draw(text);
    window.draw(mText);
    window.draw(mInstructionText);
}

bool CreditsState::update(sf::Time dt){
    if(mWorldView.getCenter().y < mText.getPosition().y)
        mWorldView.move(viewSpeed * dt.asSeconds());
    else{
        sf::Color color = mInstructionText.getFillColor();
        if(color.a == 255)
            return false;        
        mElapsedTime += dt;
        color.a = std::min(255, (int)round(mElapsedTime.asSeconds() * 255 / 2));
        mInstructionText.setFillColor(color);
    }
    return false;
}

bool CreditsState::handleEvent(const sf::Event& event){
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return false;
}

void CreditsState::handleRealTimeInput(){
    return;
}

void CreditsState::setNewText(const std::string& text, const int& cnt, const sf::Font& font, unsigned int size, const sf::Color& color){
    sf::Vector2f centerPos = mSpawnPosition + sf::Vector2f(0.f, cnt * add_y);
    sf::Text newText(text, font, size);
    newText.setFillColor(color);
    centerOrigin(newText);
    newText.setPosition(centerPos);
    mTexts.push_back(newText);
}