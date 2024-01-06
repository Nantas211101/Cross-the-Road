#pragma once
#include <Entity.hpp>
#include <DataTable.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <CommandQueue.hpp>

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
      IceCreamTruck,
      SantaClaus,
      TypeCount
   };
   
public:
   Vehicle(Type type, const TextureHolder& texture);
   Type getType();
   virtual sf::FloatRect getBoundingRect() const;
   virtual unsigned int getCategory() const;
   int getDamage();
   void playLocalSound(CommandQueue& commands);

private:
   virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
   void updateCurrent(sf::Time dt);
private:
   Type type;
   sf::Sprite sprite;
};