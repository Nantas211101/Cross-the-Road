#include "../../include/World/SceneNode.h"

#include <algorithm>
#include <cassert>

SceneNode::SceneNode()
: mChildren()
, mParent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

void SceneNode::attachChild(std::vector<Ptr> children) {
	for(int i = 0; i < children.size(); i++) {
		children[i]->mParent = this;
		mChildren.push_back(std::move(children[i]));
	}
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

std::vector<SceneNode::Ptr> SceneNode::detachChild() {
	std::vector<Ptr> result;
	for(int i = mChildren.size() - 1; i >= 0; i--) {
		Ptr child = std::move(mChildren[i]);
		child->mParent = nullptr;
		mChildren.erase(mChildren.begin() + i);
		result.push_back(std::move(child));
	}
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time)
{
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (Ptr& child : mChildren)
		child->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);

	// Draw bounding rectangle - disabled by default
	drawBoundingRect(target, states);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& child : mChildren)
		child->draw(target, states);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

auto SceneNode::getCategory() const -> unsigned int
{
    return Category::Scene;
}

void SceneNode::onCommand(const Command &command, sf::Time dt)
{
    if (command.category & getCategory()){
        command.action(*this, dt);
    }

    for (Ptr &child : mChildren)
        child->onCommand(command, dt);
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}