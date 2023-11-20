#include "../include/Road.h"
#include "TextureHolder.h"

namespace {
    const std::vector<AnimalData> TableAnimal = initializeAnimalData();
}
// 50: width each lane

void Road::loadTexture(){
    textureHolder.load(Textures::Elephant, "../../Media/Textures/Elephant.png");
    textureHolder.load(Textures::Bird, "../../Media/Textures/Bird.png");
    textureHolder.load(Textures::Rhinoceros, "../../Media/Textures/Rhinoceros.png");
}

Road::Road(sf::Vector2f spawnPos, const TextureHolder& texture)
: Lane()
,animals()
, startPos(spawnPos) {
    sprite.setTexture(texture.get(Textures::Road));
    sf::IntRect textureRect(0, 0, 3000, 150);
    //sprite.scale(0.5f,0.6f);
    sprite.setTextureRect(textureRect);
    loadTexture();
    generateAnimal();
}

void Road::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}

void Road::updateCurrent(sf::Time dt){
    Entity::updateCurrent(dt);

    if(!this->isReverse() && animals[firstAnimalIndex]->getPosition().x >= 0) {
        animals[lastAnimalIndex]->setPosition(-TableAnimal[animals[lastAnimalIndex]->getType()].distanceBetweenAnimal, startPos.y + 75);
        firstAnimalIndex = lastAnimalIndex;
        lastAnimalIndex = (lastAnimalIndex + numOfAnimal - 1) % numOfAnimal;
    }
    if(this->isReverse() && animals[lastAnimalIndex]->getPosition().x <= 2500) {
        animals[firstAnimalIndex]->setPosition(TableAnimal[animals[firstAnimalIndex]->getType()].distanceBetweenAnimal + 2500, startPos.y + 75);
        lastAnimalIndex = firstAnimalIndex;
        firstAnimalIndex = (firstAnimalIndex + 1) % numOfAnimal;
    }

}

void Road::generateAnimal(){
    int distance = 0;
    int randomKindAnimal = 1 + rand() % 3;
    Animal::Type kind;
    switch(randomKindAnimal) {
    case 1:
        kind = Animal::Elephant;
        break;
    case 2:
        kind = Animal::Bird;
        break;
    case 3:
        kind = Animal::Rhinoceros;
        break;
    }
    int randSpawnPos = rand() % 200;
    for(int j = 0; j < numOfAnimal; j++) {
        std::unique_ptr<Animal> animal(new Animal(kind, textureHolder));
        if(!this->isReverse()){
            animal->setVelocity(1.0 * TableAnimal[kind].speed, 0);
            animal->scale(TableAnimal[kind].scaling.x,TableAnimal[kind].scaling.y);
        }
        else{
            animal->setVelocity(-1.0 * TableAnimal[kind].speed, 0);
            animal->scale(-TableAnimal[kind].scaling.x,TableAnimal[kind].scaling.y);
        }
        animal->setPosition(startPos.x + randSpawnPos + distance, startPos.y + 75);
        distance += TableAnimal[kind].distanceBetweenAnimal;
        animals.push_back(animal.get());
        this->attachChild(std::move(animal));
    }

    lastAnimalIndex = numOfAnimal - 1;
    firstAnimalIndex = 0;
}
