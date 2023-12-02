#pragma once
#include <SFML/Graphics.hpp>

#include "GUI_Component.hpp"

#include <assert.h>
#include <vector>
#include <memory>

namespace GUI
{

class ContainerSet : public Component{

public:
    typedef std::shared_ptr<ContainerSet> Ptr;

public:
    ContainerSet();
    void pack(Component::Ptr component);
    virtual bool isSelectable() const;
    virtual bool isContain(const sf::RenderWindow& window) const;
    virtual void handleEvent(const sf::Event &event);
    virtual void handleRealTimeInput(const sf::RenderWindow& window);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    auto hasSelection() const -> bool;
    auto hasActivate() const -> bool;
    void activate(std::size_t index);
    void select(std::size_t index);
    void deselect();
    void selectNext();
    void selectPrev();

private:
    std::vector<Component::Ptr> mChildren;
    int mSelectedChild;
    int mActivateChild;
    bool isSelectByMouse;
    sf::Vector2i preMousePos;
    bool isJustStart;
};

}