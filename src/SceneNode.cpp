#include "SceneNode.hpp"
#include <iostream>

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

auto SceneNode::detachChild(const SceneNode &node) -> Ptr
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr &p) -> bool
                              { return p.get() == &node; }); // check the element's pointer p.get() == address of the node or not
    assert(found != mChildren.end());

    auto result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found); // erase iterator
    return result;          // return unique_ptr 
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // *= is a operator to combines the parent's absolute transform (states) with the current node's relative one (target). result will be the current node
    drawCurrent(target, states);

    // Way 1 of iteration
    for (const Ptr &child : mChildren)
    {
        child->draw(target, states);
    }

    // Way 2 of iteration
    // for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
    // {
    //     (*itr)->draw(target, states);
    // }
}

void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
    for (const Ptr &child : mChildren)
        child->update(dt);
}

auto SceneNode::getWorldTransform() -> sf::Transform const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode *node = this; node != nullptr; node = node->mParent)
        transform = node->getTransform() * transform; // reverse the operator of combining in the SceneNode::draw
    return transform;
}

auto SceneNode::getWorldPosition() -> sf::Vector2f const
{
    return getWorldTransform() * sf::Vector2f();
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