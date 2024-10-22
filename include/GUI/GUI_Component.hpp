#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "ComponentIdentifiers.hpp"

namespace GUI
{ // put in the namespace to prevent the conflix of the component

class Component
: public sf::Drawable
, public sf::Transformable
, private sf::NonCopyable                    
{

public:
    typedef std::shared_ptr<Component> Ptr;

public:
    Component();
    virtual ~Component();
    
    virtual void update(sf::Time dt); // additional for InputButton

    // virtual std::string takeSaveText() = 0;
    virtual bool isSelectable() const = 0;
    virtual bool isContain(const sf::RenderWindow& window) const = 0;
    bool isSelected() const;
    virtual void select();
    virtual void deselect();
    virtual bool isActive() const;
    virtual void activate();
    virtual void deactivate();
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void handleRealTimeInput(const sf::RenderWindow& window);
    virtual bool checkToggle();
    bool contain(sf::Vector2i mouse_pos, sf::FloatRect bounds) const;
    void setTypeOfButton(Components::ID id);
    Components::ID getTypeOfButton();

private:
    bool mIsSelected;
    bool mIsActive;
    Components::ID id;
};

}