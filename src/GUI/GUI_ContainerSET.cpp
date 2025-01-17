#include "GUI_ContainerSET.hpp"

#include <iostream>

namespace GUI
{

ContainerSet::ContainerSet()
: mChildren()
, mSelectedChild(-1)
, mActivateChild(-1)
, isSelectByMouse(true)
, preMousePos()
, isJustStart(true)
{

}

void ContainerSet::pack(Component::Ptr component)
{
    mChildren.push_back(component);
    // if (!hasSelection() && component->isSelectable())
    // select(mChildren.size() - 1);
}

bool ContainerSet::isSelectable() const
{
	return false;
}

bool ContainerSet::isContain(const sf::RenderWindow& window) const 
{
	return false;
}

void ContainerSet::handleEvent(const sf::Event& event)
{
    // If we have selected and activated a child then give it events
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
	{
		mChildren[mSelectedChild]->handleEvent(event);
	}
	// else if (event.type == sf::Event::KeyReleased)
	// {
	// 	if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
	// 	{
	// 		isSelectByMouse = false;
	// 		selectPrev();
	// 	}
	// 	else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
	// 	{
	// 		isSelectByMouse = false;
	// 		selectNext();
	// 	}
	// 	else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
	// 	{
	// 		if (hasSelection())
	// 			mChildren[mSelectedChild]->activate();
	// 	}
	// }
	isJustStart = 0;
}

void ContainerSet::handleRealTimeInput(const sf::RenderWindow& window){
	int indexContain = -1;
	for(int i = 0; i < mChildren.size(); ++i)
		if(mChildren[i]->isSelectable() && mChildren[i]->isContain(window))
			indexContain = i;
	
	sf::Vector2i curPos = sf::Mouse::getPosition(window);
	if(indexContain >= 0){
		if(!isJustStart && preMousePos != curPos){
			select(indexContain);
			isSelectByMouse = true;
		}
	}
	else{ 
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && hasSelection())
			deselect();
		if(isSelectByMouse)
			deselect();
	}
	
	if(hasSelection() && mChildren[mSelectedChild]->isContain(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mChildren[mSelectedChild]->activate();

	preMousePos = curPos;
	isJustStart = 0;
}

void ContainerSet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for(const Component::Ptr& child : mChildren)
		target.draw(*child, states);
}

bool ContainerSet::hasSelection() const
{
	return mSelectedChild >= 0;
}

bool ContainerSet::hasActivate() const
{
	return mActivateChild >= 0;
}

void ContainerSet::activate(std::size_t index)
{
	if(mChildren[index]->isSelectable()){
		if(hasActivate())
			mChildren[mActivateChild]->deactivate();
		
		if(hasSelection())
			mChildren[mSelectedChild]->deselect();
		mChildren[index]->select();
		mChildren[index]->activate();
		mSelectedChild = index;
		mActivateChild = index;

	}
}

void ContainerSet::select(std::size_t index)
{
	if(mChildren[index]->isSelectable()){
		if(hasSelection())
			mChildren[mSelectedChild]->deselect();
		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void ContainerSet::deselect()
{
	if(hasSelection()){
		mChildren[mSelectedChild]->deselect();
		mSelectedChild = -1;
	}
}

void ContainerSet::selectNext()
{
	if(!hasSelection()){
		for(int index = 0; index < mChildren.size(); ++index)
			if(mChildren[index]->isSelectable()){
				select(index);
				return;
			}
		return;
	}
	int next = mSelectedChild;
	do {
		next = (next + 1) % mChildren.size();
	} while(!mChildren[next]->isSelectable());
	select(next);
}

void ContainerSet::selectPrev()
{
	if(!hasSelection()){
		for(int index = mChildren.size() - 1; index >= 0; --index)
			if(mChildren[index]->isSelectable()){
				select(index);
				return;
			}
		return;
	}
	int prev = mSelectedChild;
	do {
		prev = (prev - 1 + mChildren.size()) % mChildren.size();
	} while(!mChildren[prev]->isSelectable());
	select(prev);
}

}