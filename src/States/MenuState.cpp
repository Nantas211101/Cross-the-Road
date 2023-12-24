#include "MenuState.hpp"

#include "TextureManipulate.hpp"
#include "GUI_Button.hpp"

namespace canvaPosition{
    const sf::Vector2f playButtonPos = sf::Vector2f(573, 569);
    const sf::Vector2f settingsButtonPos = sf::Vector2f(174, 610);
    const sf::Vector2f logoutButtonPos = sf::Vector2f(177, 733);
    const sf::Vector2f exitButtonPos = sf::Vector2f(174, 850);
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

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(LogoutButton);
	mGUIContainer.pack(exitButton);

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
    mGUIContainer.update(dt);
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
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