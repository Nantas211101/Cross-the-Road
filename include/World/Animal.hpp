#pragma once
#include <Entity.hpp>
#include <DataTable.hpp>
#include <Animation.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics.hpp>

class Animal : public Entity {
public:
   enum Type {
      Elephant,
      Rhinoceros,
      Cow,

      Small_Dragon,
      Green_Dragon,
      Red_Dragon,
      Blue_Twin_Head_Dragon,
      //Buffalo,
      //Hippo,
      Monster1,
      
      TypeCount
   };
public:
   Animal(Type type, const TextureHolder& texture);
   int getDamage();
   Type getType();
    
private:
   virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
   void updateCurrent(sf::Time dt);

private:
   Type type;
   int dmg;
   Animation sprite;
};