#pragma once

#include "Category.hpp"
#include "Command.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <assert.h>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;

public:
    SceneNode();

public:
    void attachChild(Ptr child);
    auto detachChild(const SceneNode &node) -> Ptr;

    // Updating
    void update(sf::Time dt);

    // Transform
    auto getWorldTransform() -> sf::Transform const;
    auto getWorldPosition() -> sf::Vector2f const;

    void onCommand(const Command& command, sf::Time dt);
    virtual unsigned int getCategory() const;

private:
    // the window class will internally call these 2 method
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);

private:
    std::vector<Ptr> mChildren;
    SceneNode *mParent;
};