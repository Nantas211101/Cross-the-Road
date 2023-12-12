#include "MenuState.hpp"

#include "TextureManipulate.hpp"
#include "GUI_Button.hpp"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
, mWorldView(context.window->getDefaultView())
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
{   
    sf::Vector2f pos = context.window->getView().getSize();
    float add_y = pos.y / 5;

	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->centerOrigin();
    playButton->setPosition(pos.x / 2.f, add_y * 2);
	playButton->setText("PLAY");
    playButton->setScale(0.8, 0.8);
    playButton->setColor(sf::Color::Cyan);
	playButton->setCallback([this] ()
	{
		requestStackPop();
		// requestStackPush(States::Login);
        requestStackPush(States::ChooseChar);
	});

    mText.setFont(context.fonts->get(Fonts::Main));
    mText.setString("Crossy the road");
    mText.setCharacterSize(75);
    setCenterOrigin(mText);
    mText.setPosition({pos.x / 2.f, add_y - playButton->getSize().y / 2});

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    settingsButton->centerOrigin();
	settingsButton->setPosition(pos.x / 2.f, add_y * 3);
	settingsButton->setText("SETTINGS");
    settingsButton->setScale(0.8, 0.8);
    settingsButton->setColor(sf::Color::Cyan);
	settingsButton->setCallback([this] ()
	{   
		requestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->centerOrigin();
    exitButton->setPosition(pos.x / 2.f, add_y * 4);
	exitButton->setText("Exit");
    exitButton->setScale(0.8, 0.8);
    exitButton->setColor(sf::Color::Cyan);
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(exitButton);

    buildScene();
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    // window.draw(mBackgroundSprite);
    window.draw(mSceneGraph);
    window.draw(mGUIContainer);
    window.draw(mText);
}

bool MenuState::update(sf::Time dt)
{
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
    sf::Texture& texture = (*getContext().textures).get(Textures::ChooseCharScreen);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

	// Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
}