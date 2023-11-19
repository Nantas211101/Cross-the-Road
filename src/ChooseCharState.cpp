#include "ChooseCharState.hpp"

#include "ResourceIdentifiers.hpp"
#include "TextureManipulate.hpp"
#include "GUI_Button.hpp"
#include "GUI_InputButton.hpp"
#include "SpriteNode.hpp"

#include <memory>
#include <iostream>

const float speedUp = 1000.f;

ChooseCharState::ChooseCharState(StateStack &stack, Context context)
: State(stack, context)
, mText()
, mWorldView(context.window->getDefaultView())
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f)
, mPlayer(nullptr)
, isMove(false)
, isPressing(false)
, isChange(false)
, isFocus(true)
, mGUIContainer()
, mGUIContainerSet()
{
    sf::Vector2f pos = context.window->getView().getSize();
    mText.setFont(context.fonts->get(Fonts::Main));
    mText.setString("Choose your character");
    mText.setCharacterSize(75);
    setCenterOrigin(mText);
    mText.setPosition({pos.x / 2.f, 50.f});
	
	auto rightButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures, Textures::RightButton);
	rightButton->centerOrigin();
	rightButton->setScale(0.5, 0.5);
	rightButton->setPosition(mWorldBounds.width - 150.f, mSpawnPosition.y);
	rightButton->setCallback([this] ()
	{
		startRight();
	});

	auto leftButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures, Textures::LeftButton);
	leftButton->centerOrigin();
	leftButton->setScale(0.5, 0.5);
	leftButton->setPosition(150.f, mSpawnPosition.y);
	leftButton->setCallback([this]()
	{
		startLeft();
	});



	auto chooseButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	chooseButton->centerOrigin();
	chooseButton->setColor(sf::Color::Cyan);
	chooseButton->setPosition(mSpawnPosition.x, mWorldBounds.height - 100.f);
	chooseButton->setText("Accept");
	chooseButton->setScale(0.8, 0.8);
	chooseButton->setCallback([this, context](){
		if(!isMove)
		{	
			context.player->setTextureID(this->mPlayer->getTextureID());
			requestStackPop();
			requestStackPush(States::Game);
		}
	});

	auto inputNameButton = std::make_shared<GUI::InputButton>(*context.fonts, *context.textures);
	inputNameButton->centerOrigin();
	// inputNameButton->setColor(sf::Color::Cyan);
	inputNameButton->setPosition(mSpawnPosition.x, 200.f);
	inputNameButton->setText("Your Name");
	inputNameButton->setScale(0.5, 0.5);
	inputNameButton->setToggle(true);

	inputNameButton->setCallback([this, context](std::string st){
		// if(!isMove)
		// {	
			// context.player->setTextureID(this->mPlayer->getTextureID());
			// requestStackPop();
			// requestStackPush(States::Game);
		name = st;
			// std::cerr << "Hello\n";
		// }
	});
	// std::cerr << name;

	mGUIContainerSet.pack(rightButton);
	mGUIContainerSet.pack(leftButton);
	mGUIContainerSet.pack(chooseButton);
	mGUIContainer.pack(inputNameButton);
    buildScene();
}

bool ChooseCharState::update(sf::Time elapsedTime){
    if(!isFocus)
        return false;

    impleChangeChar(elapsedTime);

	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();
	// If player touches borders, stop the action
	if (position.x <= mWorldBounds.left //150.f
	 || position.x >= mWorldBounds.width)
	{
		mPlayer->setVelocity(0, 0);
		tmpPlayer->setVelocity(0, 0);

		mSceneLayers[Air]->detachChild(*mPlayer);
		mPlayer = tmpPlayer;
		isMove = 0;
	}

	
	// Apply movements
	mSceneGraph.update(elapsedTime);
    
    return true;
}

void ChooseCharState::draw(){   
    sf::RenderWindow &mWindow = *getContext().window;
    mWindow.draw(mSceneGraph);
	mWindow.draw(mGUIContainer);
	mWindow.draw(mGUIContainerSet);
    mWindow.draw(mText);
}

bool ChooseCharState::handleEvent(const sf::Event &event){

    if(event.type == sf::Event::LostFocus)
        isFocus = false;

    if(event.type == sf::Event::GainedFocus)
        isFocus = true;
    
    if(!isFocus)
        return false;

    if(event.type == sf::Event::KeyPressed)
        handlePlayerInput(event.key.code, true);
    else 
        if(event.type == sf::Event::KeyReleased)
            handlePlayerInput(event.key.code, false);
	sf::RenderWindow &mWindow = *getContext().window;
	mGUIContainer.handleRealTimeInput(mWindow);
	mGUIContainer.handleEvent(event);

	mGUIContainerSet.handleRealTimeInput(mWindow);
	mGUIContainerSet.handleEvent(event);
    return true;
}

void ChooseCharState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
    if(!isMove && !isPressing)
		isChange = 0;
	// Change main character display when using arrow
	if(isPressed && !isChange){
		if(key == sf::Keyboard::Left){
			isChangeKey = key;
			isChange = isMove = isPressing = 1;
			std::unique_ptr<MainChar> leader(new MainChar(mPlayer->getTextureType(), *getContext().textures));
			tmpPlayer = leader.get();
			tmpPlayer->setPosition(0, mPlayer->getPosition().y);
			tmpPlayer->setVelocity(0, 0);
			tmpPlayer->setScale(0, 0);
			mSceneLayers[Air]->attachChild(std::move(leader));
			tmpPlayer->changeTexture(0, *getContext().textures);
		}
		if(key == sf::Keyboard::Right){
			isChangeKey = key;
			isChange = isMove = isPressing = 1;
			std::unique_ptr<MainChar> leader(new MainChar(mPlayer->getTextureType(), *getContext().textures));
			tmpPlayer = leader.get();
			tmpPlayer->setPosition(mWorldBounds.width, mPlayer->getPosition().y);
			tmpPlayer->setVelocity(0, 0);
			tmpPlayer->setScale(0, 0);
			mSceneLayers[Air]->attachChild(std::move(leader));
			tmpPlayer->changeTexture(1, *getContext().textures);
		}
	}

    if(isPressed && key == sf::Keyboard::Escape){
        requestStackPush(States::Pause);
    }

	if(!isPressed && isPressing && key == isChangeKey)
		isPressing = 0;
}

void ChooseCharState::startRight(){
	if(!isMove && !isPressing)
		isChange = 0;
	// Change main character display when using arrow
	if(!isChange){
		isChangeKey = sf::Keyboard::Right;
		isChange = isMove = isPressing = 1;
		std::unique_ptr<MainChar> leader(new MainChar(mPlayer->getTextureType(), *getContext().textures));
		tmpPlayer = leader.get();
		tmpPlayer->setPosition(mWorldBounds.width, mPlayer->getPosition().y);
		tmpPlayer->setVelocity(0, 0);
		tmpPlayer->setScale(0, 0);
		mSceneLayers[Air]->attachChild(std::move(leader));
		tmpPlayer->changeTexture(1, *getContext().textures);
	}
	isPressing = 0;
}

void ChooseCharState::startLeft(){
	if(!isMove && !isPressing)
		isChange = 0;
	// Change main character display when using arrow
	if(!isChange){
		isChangeKey = sf::Keyboard::Left;
		isChange = isMove = isPressing = 1;
		std::unique_ptr<MainChar> leader(new MainChar(mPlayer->getTextureType(), *getContext().textures));
		tmpPlayer = leader.get();
		tmpPlayer->setPosition(0, mPlayer->getPosition().y);
		tmpPlayer->setVelocity(0, 0);
		tmpPlayer->setScale(0, 0);
		mSceneLayers[Air]->attachChild(std::move(leader));
		tmpPlayer->changeTexture(0, *getContext().textures);
	}
	isPressing = 0;
}

void ChooseCharState::impleChangeChar(sf::Time dt){
    if(!isMove)
		return;
	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();
	int dist, naturalDist;
	float tmp;
	if(isChangeKey == sf::Keyboard::Right)
		changeRight(dt);
	else 
		if(isChangeKey == sf::Keyboard::Left)
			changeLeft(dt);
	// if(isChangeKey == sf::Keyboard::Right){
	// 	mPlayer->accelerate(-speedUp * dt.asSeconds(), 0);
	// 	dist = position.x - mWorldBounds.left;
	// 	naturalDist = mSpawnPosition.x - mWorldBounds.left;
	// 	tmp = dist * 1.0 / naturalDist;
	// 	if(tmp < 0)
	// 		tmp = 0;
	// 	mPlayer->setScale(tmp, tmp);
	// }
	// else 
	// 	if(isChangeKey == sf::Keyboard::Left){
	// 		mPlayer->accelerate(speedUp * dt.asSeconds(), 0);
	// 		dist = mWorldBounds.width - position.x;
	// 		naturalDist = mWorldBounds.width - mSpawnPosition.x;
	// 		tmp = dist * 1.0 / naturalDist;
	// 		if(tmp < 0)
	// 			tmp = 0;
	// 		mPlayer->setScale(tmp, tmp);
	// }

	// // tmp player;
	// position = tmpPlayer->getPosition();
	// velocity = tmpPlayer->getVelocity();
	// if(isChangeKey == sf::Keyboard::Right){
	// 	tmpPlayer->accelerate(-speedUp * dt.asSeconds(), 0);
	// 	dist = position.x - mSpawnPosition.x;
	// 	naturalDist = mWorldBounds.width - mSpawnPosition.x;
	// 	tmp = 1 - (dist * 1.0 / naturalDist);
	// 	if(tmp < 0)
	// 		tmp = 0;
	// 	tmpPlayer->setScale(tmp, tmp);
	// }
	// else 
	// 	if(isChangeKey == sf::Keyboard::Left){
	// 		tmpPlayer->accelerate(speedUp * dt.asSeconds(), 0);
	// 		dist = mSpawnPosition.x - position.x;
	// 		naturalDist = mSpawnPosition.x - 0;
	// 		tmp = 1 - (dist * 1.0 / naturalDist);
	// 		if(tmp < 0)
	// 			tmp = 0;
	// 		tmpPlayer->setScale(tmp, tmp);
	// }
}

void ChooseCharState::changeRight(sf::Time dt){
	int dist, naturalDist;
	float tmp;
	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();
	// mPlayer
	mPlayer->accelerate(-speedUp * dt.asSeconds(), 0);
	dist = position.x - mWorldBounds.left;
	naturalDist = mSpawnPosition.x - mWorldBounds.left;
	tmp = dist * 1.0 / naturalDist;
	if(tmp < 0)
		tmp = 0;
	mPlayer->setScale(tmp, tmp);
	////////////////////////////

	position = tmpPlayer->getPosition();
	velocity = tmpPlayer->getVelocity();
	
	// tmp
	tmpPlayer->accelerate(-speedUp * dt.asSeconds(), 0);
	dist = position.x - mSpawnPosition.x;
	naturalDist = mWorldBounds.width - mSpawnPosition.x;
	tmp = 1 - (dist * 1.0 / naturalDist);
	if(tmp < 0)
		tmp = 0;
	tmpPlayer->setScale(tmp, tmp);
}

void ChooseCharState::changeLeft(sf::Time dt){
	int dist, naturalDist;
	float tmp;
	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();
	// mPlayer
	mPlayer->accelerate(speedUp * dt.asSeconds(), 0);
	dist = mWorldBounds.width - position.x;
	naturalDist = mWorldBounds.width - mSpawnPosition.x;
	tmp = dist * 1.0 / naturalDist;
	if(tmp < 0)
		tmp = 0;
	mPlayer->setScale(tmp, tmp);
	/////////////////////////////////////

	position = tmpPlayer->getPosition();
	velocity = tmpPlayer->getVelocity();

	// tmpPlayer
	tmpPlayer->accelerate(speedUp * dt.asSeconds(), 0);
	dist = mSpawnPosition.x - position.x;
	naturalDist = mSpawnPosition.x - 0;
	tmp = 1 - (dist * 1.0 / naturalDist);
	if(tmp < 0)
		tmp = 0;
	tmpPlayer->setScale(tmp, tmp);
}

void ChooseCharState::handleRealTimeInput(){
    return;
}

void ChooseCharState::buildScene(){
    // Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = (getContext().textures)->get(Textures::ChooseCharScreen);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's aircraft / chicken
	createMainChar();
}

void ChooseCharState::createMainChar(){
    std::unique_ptr<MainChar> leader(new MainChar(MainChar::Sheep, *getContext().textures));
	mPlayer = leader.get();
	mPlayer->setPosition(mSpawnPosition);
	mPlayer->setVelocity(0, 0);
	mSceneLayers[Air]->attachChild(std::move(leader));
}