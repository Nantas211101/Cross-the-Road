#pragma once
#include "ResourceHolder.hpp"
#include "SceneNode.hpp"
#include <SFML\Graphics.hpp>
// namespace Textures
// {
//     enum ID
//     {
//         Eagle,
//         Raptor,
//     };
// }

// typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Entity : public SceneNode {
  public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    auto getVelocity() const -> sf::Vector2f;
    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);

  private:
    virtual void updateCurrent(sf::Time dt);

  private:
    sf::Vector2f mVelocity;
};