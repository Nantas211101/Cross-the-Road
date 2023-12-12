#include "Entity.hpp"

#include <assert.h>

Entity::Entity()
: mVelocity()
, mHitPoints(0)
{ // additional

}

Entity::Entity(int hitpoints)
: mVelocity()
, mHitPoints(hitpoints)
{ // additional

}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

void Entity::repair(int points)
{
	if(mHitPoints <= 0)
		throw std::invalid_argument("Entity::repair - Repairing a HP <= 0 entity!");

	mHitPoints += points;
}

void Entity::damage(int points)
{
	if(mHitPoints <= 0)
		throw std::invalid_argument("Entity::damage - Damaging a HP <= 0 entity!");
	
	mHitPoints -= points;
}

void Entity::destroy()
{
	mHitPoints = 0;
}

int Entity::getHitPoints()
{
	return mHitPoints;
}

bool Entity::isDestroyed() const
{
	return mHitPoints <= 0;
}

void Entity::updateCurrent(sf::Time dt)
{	
	move(mVelocity * dt.asSeconds());
}