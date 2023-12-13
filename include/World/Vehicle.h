#pragma once
#include <Entity.h>
#include <DataTable.h>
#include <ResourceIdentifiers.h>
#include <ResourceHolder.h>

#include <SFML/Graphics.hpp>

class Vehicle:public Entity{
public:
   enum Type{
      Truck,
      BlueCar,
      YellowCar,
      SmallCar,
      Ambulance,
      PoliceCar,
      SuperCar,
      OldCar,
      TypeCount
   };
   
public:
   Vehicle(Type type, const TextureHolder& texture);
   Type getType();
   virtual sf::FloatRect getBoundingRect() const;
   virtual unsigned int getCategory() const;
   int getDamage();

private:
   virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
   void updateCurrent(sf::Time dt);
private:
   Type type;
   sf::Sprite sprite;
};