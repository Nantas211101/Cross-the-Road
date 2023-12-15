#pragma once

#include "GUI_Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics.hpp>
#include <string>

namespace GUI
{

class Label : public Component
{

public:
    typedef std::shared_ptr<Label> Ptr;

public:
    Label(const std::string& text, const FontHolder& fonts);

    virtual bool isSelectable() const;
    virtual bool isContain(const sf::RenderWindow& window) const;
    void setText(const std::string& text);
    // void setColor(sf::Color color);
    
    virtual void handleEvent(const sf::Event& event);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Text			mText;
};

}