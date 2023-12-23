#include <SpriteNode.hpp>

#include <SFML/Graphics/RenderTarget.hpp>


SpriteNode::SpriteNode(const sf::Texture& texture)
: mSprite(texture)
{
}	

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
: mSprite(texture, textureRect)
{
}

void SpriteNode::setTextureRect(sf::IntRect rect)
{
	mSprite.setTextureRect(rect);
}

void SpriteNode::setTextureRect(sf::Vector2f topLeft, int width, int height)
{
	mSprite.setTextureRect(sf::IntRect(topLeft.x, topLeft.y, width, height));
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}