#include <TextNode.hpp>

TextNode::TextNode(const FontHolder& fonts, const std::string& text)
: mText(text, fonts.get(Fonts::Main), 20)
, mPosition(0, 50)
{
	mText.setPosition(mPosition);
	setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText, states);
}

void TextNode::setString(const std::string& text)
{
	mText.setString(text);
	centerOrigin(mText);
}

void TextNode::setFillColor(sf::Color color)
{
	mText.setFillColor(color);
}

void TextNode::setCharacterSize(int size)
{
	mText.setCharacterSize(size);
	setString(mText.getString());
	mText.setPosition(mPosition);
}

void TextNode::setRelativePosition(sf::Vector2f pos)
{
	mPosition = pos;
	mText.setPosition(mPosition);
}