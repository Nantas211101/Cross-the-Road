#include "ChooseCharState.hpp"

#include "ResourceIdentifiers.hpp"
#include "TextureManipulate.hpp"
#include "GUI_Button.hpp"
#include "SpriteNode.hpp"
#include "Utility.hpp"
#include "BitMaskingManipulate.hpp"

#include <memory>
#include <iostream>

const float scaleCharacter = 5.f;
const float startSpeedUp = 1000.f;
float speedUp = 1000.f;
const std::string Error_Do_Not_Have_This_Character = "You do not have this character!";

ChooseCharState::ChooseCharState(StateStack &stack, Context context)
: State(stack, context)
, mText("Choose your character", context.fonts->get(Fonts::Main), 75)
, mWorldView(context.window->getDefaultView())
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f)
, mPlayer(nullptr)
, tmpPlayer(nullptr)
, isMove(false)
, isPressing(false)
, isChange(false)
, isFocus(true)
// , mGUIContainer()
, mGUIContainerSet()
, maskID(0)
, uidDisplay("", context.fonts->get(Fonts::Main), 25)
, ErrorText("", context.fonts->get(Fonts::Main), 50)
{
    sf::Vector2f pos = context.window->getView().getSize();
    setCenterOrigin(mText);
    mText.setPosition({pos.x / 2.f, 50.f});
	
	auto rightButton = std::make_shared<GUI::Button>(context, Textures::RightButton);
	rightButton->centerOrigin();
	rightButton->setScale(0.5, 0.5);
	rightButton->setPosition(mWorldBounds.width - 150.f, mSpawnPosition.y);
	rightButton->setCallback([this] ()
	{
		speedUp = startSpeedUp;
		callError("");
		startRight();
	});


	auto leftButton = std::make_shared<GUI::Button>(context, Textures::LeftButton);
	leftButton->centerOrigin();
	leftButton->setScale(0.5, 0.5);
	leftButton->setPosition(150.f, mSpawnPosition.y);
	leftButton->setCallback([this]()
	{
		speedUp = startSpeedUp;
		callError("");
		startLeft();
	});

	ErrorText.setFillColor(sf::Color::Red);
	centerOrigin(ErrorText);
	ErrorText.setPosition(mSpawnPosition.x, mWorldBounds.height - 200.f);

	auto chooseButton = std::make_shared<GUI::Button>(context);
	chooseButton->centerOrigin();
	chooseButton->setColor(sf::Color::Cyan);
	chooseButton->setPosition(mSpawnPosition.x, mWorldBounds.height - 100.f);
	chooseButton->setText("Accept");
	chooseButton->setScale(0.8, 0.8);
	chooseButton->setCallback([this, context](){
		PlayGame();
	});

	auto backButton = std::make_shared<GUI::Button>(context, Textures::backButton);
	backButton->centerOrigin();
	// backButton->setColor(sf::Color::Cyan);
	backButton->setPosition(350.f, mWorldBounds.height - 100.f);
	backButton->setScale(0.8, 0.8);
	backButton->setCallback([this, context](){
		BackToLogin();
	});

	auto displayCharButton = std::make_shared<GUI::Button>(context, Textures::displayButton);
	displayCharButton->centerOrigin();
	sf::Vector2f sizee = displayCharButton->getSize();
	sf::Vector2f needSize = {mWorldBounds.width / 30.f, mWorldBounds.height / 15.f};
	displayCharButton->setScale({needSize.x / sizee.x, needSize.y / sizee.y});
	displayCharButton->setPosition(mWorldBounds.width - displayCharButton->getSize().x / 1.8, mWorldBounds.height / 6.f);
	
	displayCharButton->setCallback([this](){
		requestStackPush(States::DisplayCharState);
	});

	maskID = context.player->getMaskID();
	std::string tmp = toString(context.player->getUID());
	while(tmp.size() < 7)
		tmp = "0" + tmp;
	tmp = "UID: 8" + tmp;

	uidDisplay.setString(tmp);
	centerOrigin(uidDisplay);
	sf::FloatRect boundsUID = uidDisplay.getGlobalBounds();
	uidDisplay.setPosition(mWorldView.getSize().x - boundsUID.width - 1.f, mWorldView.getSize().y - boundsUID.height - 1.f);

	mGUIContainerSet.pack(rightButton);
	mGUIContainerSet.pack(leftButton);
	mGUIContainerSet.pack(chooseButton);
	mGUIContainerSet.pack(backButton);
	mGUIContainerSet.pack(displayCharButton);

    buildScene();
	context.music->play(Music::ChooseCharTheme);
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
        // tmpPlayer = nullptr;
		mPlayer->setPosition(mSpawnPosition);
		isMove = 0;
		// speedUp = startSpeedUp;
	}
	
	// Apply movements
	mSceneGraph.update(elapsedTime);
    updateCharID();
    return true;
}

void ChooseCharState::draw(){   
    sf::RenderWindow &mWindow = *getContext().window;
    mWindow.draw(mSceneGraph);
	// mWindow.draw(mGUIContainer);
	mWindow.draw(mGUIContainerSet);
    mWindow.draw(mText);
	mWindow.draw(uidDisplay);
	mWindow.draw(ErrorText);
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
	mGUIContainerSet.handleRealTimeInput(mWindow);
	mGUIContainerSet.handleEvent(event);
    return true;
}

void ChooseCharState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
    if(!isMove)
		isChange = 0;
	// Change main character display when using arrow
	if(isPressed && !isChange){
		if(key == sf::Keyboard::Left){
			callError("");
			isChangeKey = key;
			isChange = isMove = isPressing = 1;
            MainChar::Type newID = changeTexture(mPlayer->getMainCharType(), 1);
			std::unique_ptr<MainChar> leader(new MainChar(newID, *getContext().textures, {0, mPlayer->getPosition().y}));
			tmpPlayer = leader.get();
			mSceneLayers[Air]->attachChild(std::move(leader));
			tmpPlayer->setVelocity(0, 0);
			tmpPlayer->setScale(0, 0);
            tmpPlayer->setCenterOriginMainChar();
			if((tmpPlayer->getThisMaskID() | maskID) != maskID)
				tmpPlayer->setOwnerFlag(false);
		}
		if(key == sf::Keyboard::Right){
			callError("");
			isChangeKey = key;
			isChange = isMove = isPressing = 1;
            MainChar::Type newID = changeTexture(mPlayer->getMainCharType(), 0);
			std::unique_ptr<MainChar> leader(new MainChar(newID, *getContext().textures, {mWorldBounds.width, mPlayer->getPosition().y}));
			tmpPlayer = leader.get();
			mSceneLayers[Air]->attachChild(std::move(leader));
			tmpPlayer->setVelocity(0, 0);
			tmpPlayer->setScale(0, 0);
            tmpPlayer->setCenterOriginMainChar();
			if((tmpPlayer->getThisMaskID() | maskID) != maskID)
				tmpPlayer->setOwnerFlag(false);
		}
	}

    if(isPressed && key == sf::Keyboard::Escape){
        requestStackPush(States::Pause);
    }

	if(!isPressed && isPressing && key == isChangeKey)
		isPressing = 0;
	if(!isPressed && key == isChangeKey)
		speedUp = startSpeedUp;
}

void ChooseCharState::startRight(){
	if(!isMove && !isPressing)
		isChange = 0;
	// Change main character display when using arrow
	if(!isChange){
		isChangeKey = sf::Keyboard::Right;
		isChange = isMove = isPressing = 1;
        MainChar::Type newID = changeTexture(mPlayer->getMainCharType(), 0);
		std::unique_ptr<MainChar> leader(new MainChar(newID, *getContext().textures, {mWorldBounds.width, mPlayer->getPosition().y}));
		tmpPlayer = leader.get();
		tmpPlayer->setVelocity(0, 0);
		tmpPlayer->setScale(0, 0);
        tmpPlayer->setCenterOriginMainChar();
		mSceneLayers[Air]->attachChild(std::move(leader));
		if((tmpPlayer->getThisMaskID() | maskID) != maskID)
			tmpPlayer->setOwnerFlag(false);
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
        MainChar::Type newID = changeTexture(mPlayer->getMainCharType(), 1);
		std::unique_ptr<MainChar> leader(new MainChar(newID, *getContext().textures, {0, mPlayer->getPosition().y}));
		tmpPlayer = leader.get();
		tmpPlayer->setVelocity(0, 0);
        tmpPlayer->setCenterOriginMainChar();
		tmpPlayer->setScale(0, 0);
		mSceneLayers[Air]->attachChild(std::move(leader));
		if((tmpPlayer->getThisMaskID() | maskID) != maskID)
			tmpPlayer->setOwnerFlag(false);
	}
	isPressing = 0;
}

void ChooseCharState::impleChangeChar(sf::Time dt){
    if(!isMove)
		return;
	if(speedUp < 100000.f)
		speedUp += speedUp * dt.asSeconds();
	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();
	int dist, naturalDist;
	float tmp;
	if(isChangeKey == sf::Keyboard::Right)
		changeRight(dt);
	else 
		if(isChangeKey == sf::Keyboard::Left)
			changeLeft(dt);
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
	mPlayer->setScale(tmp * scaleCharacter, tmp * scaleCharacter);
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
	tmpPlayer->setScale(tmp * scaleCharacter, tmp * scaleCharacter);
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
	mPlayer->setScale(tmp * scaleCharacter, tmp * scaleCharacter);
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
	tmpPlayer->setScale(tmp * scaleCharacter, tmp * scaleCharacter);
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
    std::unique_ptr<MainChar> leader(new MainChar(MainChar::Player1, *getContext().textures, mSpawnPosition));
    mPlayer = leader.get();
	mPlayer->setVelocity(0, 0);
    mPlayer->setCenterOriginMainChar();
    mPlayer->setScale(scaleCharacter, scaleCharacter);
	mSceneLayers[Air]->attachChild(std::move(leader));
}

void ChooseCharState::PlayGame(){
	MainChar* tmp;
	if(isMove)
		tmp = tmpPlayer;
	else 
		tmp = mPlayer;
	if((tmp->getThisMaskID() | maskID) != maskID){
		callError(Error_Do_Not_Have_This_Character);
		return;
	}
	getContext().player->setMainCharID(tmp->getMainCharType());
	requestStackPop();
	requestStackPush(States::Game);
}

void ChooseCharState::updateCharID(){
	MainChar *tmp;
	if(isMove)
		tmp = tmpPlayer;
	else 
		tmp = mPlayer;
	getContext().player->setMainCharID(tmp->getMainCharType());
}

void ChooseCharState::BackToLogin(){
	requestStackPop();
	requestStackPush(States::Login);
}

void ChooseCharState::callError(const std::string& error)
{
	sf::Vector2f pos = ErrorText.getPosition();
	ErrorText.setString(error);
	centerOrigin(ErrorText);
	ErrorText.setPosition(pos);
}