#include "MenuState.hpp"

#include "TextureManipulate.hpp"
#include "GUI_Button.hpp"

#include <fstream>

const std::string Path_SaveAccount = "PrivateInfo/AccountSaving.txt";
const std::string tmp_Account = "PrivateInfo/TmpSaving.txt";
namespace canvaPosition{
    const sf::Vector2f playButtonPos = sf::Vector2f(573, 569);
    const sf::Vector2f settingsButtonPos = sf::Vector2f(174, 610);
    const sf::Vector2f logoutButtonPos = sf::Vector2f(177, 733);
    const sf::Vector2f exitButtonPos = sf::Vector2f(174, 850);
    const sf::Vector2f creditButtonPos = sf::Vector2f(1178, 836.5);
    const sf::Vector2f resetButtonPos = sf::Vector2f(172.5, 92.5);
}

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
, mWorldView(context.window->getDefaultView())
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
{   
    sf::Vector2f pos = context.window->getView().getSize();
    float add_y = pos.y / 5;

	auto playButton = std::make_shared<GUI::Button>(context, Textures::PlayButton);
    playButton->centerOrigin();
    playButton->setPosition(canvaPosition::playButtonPos);
	playButton->setCallback([this] ()
	{
		requestStackPop();
        requestStackPush(States::ChooseWorldState);
    });

	auto settingsButton = std::make_shared<GUI::Button>(context, Textures::SettingButton);
    settingsButton->centerOrigin();
    settingsButton->setPosition(canvaPosition::settingsButtonPos);
	settingsButton->setCallback([this] ()
	{   
		requestStackPush(States::Settings);
	});

    auto LogoutButton = std::make_shared<GUI::Button>(context, Textures::LogoutButton);
    LogoutButton->centerOrigin();
    LogoutButton->setPosition(canvaPosition::logoutButtonPos);
    LogoutButton->setCallback([this] ()
    {
        saveCurrentPlayerInfo();
        requestStackPop();
        requestStackPush(States::Login);
    });

	auto exitButton = std::make_shared<GUI::Button>(context, Textures::ExitButton);
    exitButton->centerOrigin();
    exitButton->setPosition(canvaPosition::exitButtonPos);
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

    auto creditButton = std::make_shared<GUI::Button>(context, Textures::CreditButton);
    creditButton->centerOrigin();
    creditButton->setPosition(canvaPosition::creditButtonPos);
    creditButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Credits);
    });

    auto resetButton = std::make_shared<GUI::Button>(context, Textures::ResetButton);
    resetButton->centerOrigin();
    resetButton->setPosition(canvaPosition::resetButtonPos);
    resetButton->setCallback([this] ()
    {
        requestStackPush(States::ResetConfirm);
    });

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(LogoutButton);
	mGUIContainer.pack(exitButton);
    mGUIContainer.pack(creditButton);
    mGUIContainer.pack(resetButton);

    buildScene();

    context.music->play(Music::MenuTheme);
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    // window.draw(mBackgroundSprite);
    window.draw(mSceneGraph);
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time dt)
{
    mElapsedTime += dt;
    mGUIContainer.update(dt);
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    if(mElapsedTime < sf::seconds(0.4))
        return false;
    sf::RenderWindow &mWindow = *getContext().window;
	mGUIContainer.handleRealTimeInput(mWindow);
    mGUIContainer.handleEvent(event);

    return false;
}

void MenuState::buildScene(){
    // Initialize the different layers
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

	// Prepare the tiled background
    sf::Texture& texture = (*getContext().textures).get(Textures::MenuScreen);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

	// Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
}

void MenuState::saveCurrentPlayerInfo(){
    int curUID = getContext().player->getUID();

    // Read Part
    std::ifstream fi(Path_SaveAccount);
    if(!fi.is_open()){
        throw std::runtime_error("MenuState::saveCurrentPlayerInfo - Cannot open file " + Path_SaveAccount);
        return;
    }

    std::ofstream tmpFo(tmp_Account);
    if(!tmpFo.is_open()){
        throw std::runtime_error("MenuState::saveCurrentPlayerInfo - Cannot open file " + tmp_Account);
        return;
    }

    int UID;
    std::string username;
    int passwordHash[5];
    int lv;
    int money;
    int mask;

    while(fi >> UID >> username >> passwordHash[0] >> passwordHash[1] >> passwordHash[2] >> passwordHash[3] >> passwordHash[4] >> lv >> money >> mask){
        if(UID == curUID){
            lv = *getContext().limitLevel;
            money = *getContext().money;
            mask = getContext().player->getMaskID();
        }
        tmpFo << UID << "\n" << username << "\n" << passwordHash[0] << " " << passwordHash[1] << " " << passwordHash[2] << " " << passwordHash[3] << " " << passwordHash[4] << "\n" << lv << "\n" << money << "\n" << mask << "\n";
    }

    fi.close();
    tmpFo.close();

    // Write Part
    std::ifstream tmpFi(tmp_Account);
    if(!tmpFi.is_open()){
        throw std::runtime_error("MenuState::saveCurrentPlayerInfo - Cannot open file " + tmp_Account);
        return;
    }

    std::ofstream fo(Path_SaveAccount);
    if(!fo.is_open()){
        throw std::runtime_error("MenuState::saveCurrentPlayerInfo - Cannot open file " + Path_SaveAccount);
        return;
    }

    while(tmpFi >> UID >> username >> passwordHash[0] >> passwordHash[1] >> passwordHash[2] >> passwordHash[3] >> passwordHash[4] >> lv >> money >> mask){
        fo << UID << "\n" << username << "\n" << passwordHash[0] << " " << passwordHash[1] << " " << passwordHash[2] << " " << passwordHash[3] << " " << passwordHash[4] << "\n" << lv << "\n" << money << "\n" << mask << "\n";
    }

    tmpFi.close();
    fo.close();
}
