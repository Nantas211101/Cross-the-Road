#pragma once

#include <Command.hpp>
#include <Category.hpp>
#include <Utility.hpp>

#include <vector>
#include <memory>
#include <set>
#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
	public:
		typedef std::unique_ptr<SceneNode> Ptr;
		typedef std::pair<SceneNode*, SceneNode*> Pair;

	public:
		explicit				SceneNode();

		void					attachChild(Ptr child);
		void					attachChild(std::vector<Ptr> children);
		Ptr						detachChild(const SceneNode& node);
		std::vector<Ptr>		detachChild();

		void					update(sf::Time dt);

		sf::Vector2f			getWorldPosition() const;
		sf::Transform			getWorldTransform() const;
		void 					onCommand(const Command& command, sf::Time dt);
    	virtual unsigned int 	getCategory() const;

		void					checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
		void					checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
		void					removeWrecks();
		virtual sf::FloatRect	getBoundingRect() const;
		virtual bool			isMarkedForRemoval() const;
		virtual bool			isDestroyed() const;

		//Additional function
		void 					setReverse(bool flag = true);
	private:
		virtual void			updateCurrent(sf::Time dt);
		void					updateChildren(sf::Time dt);

		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 					drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const;
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::vector<Ptr>		mChildren;
		SceneNode*				mParent;
		//Additional attribute
		bool					isReverse;
};

bool	collision(const SceneNode& lhs, const SceneNode& rhs);
float	distance(const SceneNode& lhs, const SceneNode& rhs);