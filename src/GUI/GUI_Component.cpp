#include "GUI_Component.hpp"

namespace GUI
{

Component::Component()
: mIsSelected(false)
, mIsActive(false)
, id(Components::Button)
{

}

Component::~Component()
{

}

bool Component::isSelected() const
{
	return mIsSelected;
}

void Component::select()
{
	mIsSelected = true;
}

void Component::deselect()
{
	mIsSelected = false;
}

bool Component::isActive() const
{
	return mIsActive;
}

void Component::activate()
{
	mIsActive = true;
}

void Component::deactivate()
{
	mIsActive = false;
} 

void Component::handleRealTimeInput(const sf::RenderWindow& window){
	// do nothing
}

bool Component::checkToggle(){
	return false;
}

bool Component::contain(sf::Vector2i mouse_pos, sf::FloatRect bounds) const{
    sf::Vector2f cur_pos = getPosition();
	bounds.width *= getScale().x;
	bounds.height *= getScale().y; // to take globalbound

    bounds.left = cur_pos.x - bounds.width / 2;
    bounds.top = cur_pos.y - bounds.height / 2; // because center origin, we need this to contain right
    return bounds.contains(sf::Vector2f(mouse_pos));
}

void Component::setTypeOfButton(Components::ID id){
	this->id = id;
}

Components::ID Component::getTypeOfButton(){
	return this->id;
}

}