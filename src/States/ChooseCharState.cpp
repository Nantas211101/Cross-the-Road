#include "ChooseCharState.hpp"

#include "ResourceIdentifiers.hpp"
#include "TextureManipulate.hpp"
#include "GUI_Button.hpp"
#include "SpriteNode.hpp"
#include "Utility.hpp"
#include "BitMaskingManipulate.hpp"

#include <memory>
#include <iostream>

namespace canvaPosition{
	const sf::Vector2f rightButtonPos = sf::Vector2f(1355, 626);
	const sf::Vector2f leftButtonPos = sf::Vector2f(345, 626);
	const sf::Vector2f chooseButtonPos = sf::Vector2f(850, 865);
	const sf::Vector2f backButtonPos = sf::Vector2f(178.5, 95);
	const sf::Vector2f displayCharButtonPos = sf::Vector2f(1180, 865);
};

const float scaleCharacter = 5.f;
const float limitSpeed = 5000.f;
const float startSpeedUp = 1000.f;
sf::Vector2f speedMoving = {0, 0};
float speedUp = startSpeedUp;
const std::string Error_Do_Not_Have_This_Character = "You do not have this character!";

ChooseCharState::ChooseCharState(StateStack &stack, Context context)
: State(stack, context)
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
	
	auto rightButton = std::make_shared<GUI::Button>(context, Textures::RightButton);
	rightButton->centerOrigin();
	rightButton->setPosition(canvaPosition::rightButtonPos);
	rightButton->setCallback([this] ()
	{
		speedUp = startSpeedUp;
		callError("");
		startRight();
	});


	auto leftButton = std::make_shared<GUI::Button>(context, Textures::LeftButton);
	leftButton->centerOrigin();
	leftButton->setPosition(canvaPosition::leftButtonPos);
	leftButton->setCallback([this]()
	{
		speedUp = startSpeedUp;
		callError("");
		startLeft();
	});

	ErrorText.setFillColor(sf::Color::Red);
	centerOrigin(ErrorText);
	ErrorText.setPosition(mSpawnPosition.x, mWorldBounds.height - 200.f);

	auto chooseButton = std::make_shared<GUI::Button>(context, Textures::AcceptButton);
	chooseButton->centerOrigin();
	chooseButton->setPosition(canvaPosition::chooseButtonPos);
	chooseButton->setCallback([this, context](){
		PlayGame();
	});

	auto backButton = std::make_shared<GUI::Button>(context, Textures::BackButton);
	backButton->centerOrigin();
	backButton->setPosition(canvaPosition::backButtonPos);
	backButton->setCallback([this, context](){
		requestStackPop();
		requestStackPush(States::ChooseLevelState);
	});

	auto displayCharButton = std::make_shared<GUI::Button>(context, Textures::InfoButton);
	displayCharButton->centerOrigin();
	displayCharButton->setPosition(canvaPosition::displayCharButtonPos);
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
	if(!isMove)
		speedUp = startSpeedUp;

	mElapsedTime += elapsedTime;

    impleChangeChar(elapsedTime);

	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();
	// If player touches borders, stop the action
	if (position.x <= mWorldBounds.left //150.f
	 || position.x >= mWorldBounds.width)
	{
		speedMoving = {0, 0};
		mPlayer->setVelocity(0, 0);
		tmpPlayer->setVelocity(0, 0);

		mSceneLayers[Air]->detachChild(*mPlayer);
		mPlayer = tmpPlayer;
        // tmpPlayer = nullptr;
		mPlayer->setPosition(mSpawnPosition.x, canvaPosition::leftButtonPos.y);
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
	mWindow.draw(uidDisplay);
	mWindow.draw(ErrorText);
}

bool ChooseCharState::handleEvent(const sf::Event &event){

	if(mElapsedTime < sf::seconds(1.0))
		return false;

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
			std::unique_ptr<MainChar> leader(new MainChar(newID, *getContext().textures, {0, mSpawnPosition.y/*mPlayer->getPosition().y*/}));
			tmpPlayer = leader.get();
			mSceneLayers[Air]->attachChild(std::move(leader));
			speedMoving = {speedUp, 0};
			tmpPlayer->setVelocity(speedUp, 0);
			mPlayer->setVelocity(speedUp, 0);
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
			std::unique_ptr<MainChar> leader(new MainChar(newID, *getContext().textures, {mWorldBounds.width, mSpawnPosition.y /*mPlayer->getPosition().y*/}));
			tmpPlayer = leader.get();
			mSceneLayers[Air]->attachChild(std::move(leader));
			speedMoving = {-speedUp, 0};
			tmpPlayer->setVelocity(-speedUp, 0);
			mPlayer->setVelocity(-speedUp, 0);
			tmpPlayer->setScale(0, 0);
            tmpPlayer->setCenterOriginMainChar();
			if((tmpPlayer->getThisMaskID() | maskID) != maskID)
				tmpPlayer->setOwnerFlag(false);
		}
	}

    // if(isPressed && key == sf::Keyboard::Escape){
    //     requestStackPush(States::Pause);
    // }

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
        MainChar::Type newID = changeTexture(mPlayer->getMainCharType(), 0);
		std::unique_ptr<MainChar> leader(new MainChar(newID, *getContext().textures, {mWorldBounds.width, mSpawnPosition.y /*mPlayer->getPosition().y*/}));
		tmpPlayer = leader.get();
		speedMoving = {-speedUp, 0};
		tmpPlayer->setVelocity(-speedUp, 0);
		mPlayer->setVelocity(-speedUp, 0);
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
		std::unique_ptr<MainChar> leader(new MainChar(newID, *getContext().textures, {0, mSpawnPosition.y /*mPlayer->getPosition().y*/}));
		tmpPlayer = leader.get();
		speedMoving = {speedUp, 0};
		tmpPlayer->setVelocity(speedUp, 0);
		mPlayer->setVelocity(speedUp, 0);
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
	// if(speedUp < limitSpeed)
	// 	speedUp += speedUp * dt.asSeconds();
	if(isChangeKey == sf::Keyboard::Right)
		changeRight(dt);
	else 
		if(isChangeKey == sf::Keyboard::Left)
			changeLeft(dt);
	if(speedMoving.x < 0){
		mPlayer->setVelocity(speedMoving.x, mSpawnPosition.y - canvaPosition::leftButtonPos.y - 50.f);
		tmpPlayer->setVelocity(speedMoving.x, canvaPosition::leftButtonPos.y - mSpawnPosition.y + 50.f);
	}
	else{
		mPlayer->setVelocity(speedMoving.x, mSpawnPosition.y - canvaPosition::leftButtonPos.y - 50.f);
		tmpPlayer->setVelocity(speedMoving.x, canvaPosition::leftButtonPos.y - mSpawnPosition.y + 50.f);
	
	}
}

void ChooseCharState::changeRight(sf::Time dt){
	speedMoving = {-speedUp, 0};
	int dist, naturalDist;
	float tmp;
	sf::Vector2f position = mPlayer->getPosition();
	// mPlayer
	// quang duong con lai / tong quang duong 

	dist = position.x - mWorldBounds.left;
	naturalDist = mSpawnPosition.x - mWorldBounds.left;
	tmp = dist * 1.0 / naturalDist;
	if(tmp < 0)
		tmp = 0;
	mPlayer->setScale(tmp * scaleCharacter, tmp * scaleCharacter);
	////////////////////////////

	position = tmpPlayer->getPosition();
	
	// tmp
	dist = position.x - mSpawnPosition.x;
	naturalDist = mWorldBounds.width - mSpawnPosition.x;
	tmp = 1 - (dist * 1.0 / naturalDist);
	if(tmp < 0)
		tmp = 0;
	tmpPlayer->setScale(tmp * scaleCharacter, tmp * scaleCharacter);
}

void ChooseCharState::changeLeft(sf::Time dt){
	speedMoving = {speedUp, 0};
	int dist, naturalDist;
	float tmp;
	sf::Vector2f position = mPlayer->getPosition();
	// mPlayer
	dist = mWorldBounds.width - position.x;
	naturalDist = mWorldBounds.width - mSpawnPosition.x;
	tmp = dist * 1.0 / naturalDist;
	if(tmp < 0)
		tmp = 0;
	mPlayer->setScale(tmp * scaleCharacter, tmp * scaleCharacter);
	/////////////////////////////////////

	position = tmpPlayer->getPosition();

	// tmpPlayer
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
    std::unique_ptr<MainChar> leader(new MainChar(MainChar::Player1, *getContext().textures, {mSpawnPosition.x, canvaPosition::leftButtonPos.y}));
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


void ChooseCharState::callError(const std::string& error)
{
	sf::Vector2f pos = ErrorText.getPosition();
	ErrorText.setString(error);
	centerOrigin(ErrorText);
	ErrorText.setPosition(pos);
}