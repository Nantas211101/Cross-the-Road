#include "GUI_Label.hpp"

namespace GUI{

Label::Label(const std::string& text, const FontHolder& fonts)
: mText(text, fonts.get(Fonts::Label), 16)
{

}

bool Label::isSelectable() const
{
    return false;
}

bool Label::isContain(const sf::RenderWindow& window) const
{
    return false;
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) 
const
{
    states.transform *= getTransform();
    target.draw(mText, states);
}

void Label::setText(const std::string& text)
{
    mText.setString(text);
}

// void Label::setColor(sf::Color color){
//     mText.setColor(color);
// }

void Label::handleEvent(const sf::Event&)
{

}

}
