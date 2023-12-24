#pragma once
#include <SceneNode.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <Utility.hpp>

#include <string>
#include <SFML/Graphics.hpp>

class TextNode : public SceneNode
{
	public:
		explicit			TextNode(const FontHolder& fonts, const std::string& text);

		void				setString(const std::string& text);
		void 				setFillColor(sf::Color color);
		void 				setCharacterSize(int size);
		void 				setRelativePosition(sf::Vector2f pos);

	private:
		virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Text			mText;
		sf::Vector2f 		mPosition;
};