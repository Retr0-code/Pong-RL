#pragma once
#include <cmath>

#include "IGameObject.hpp"

#define ELASTICBALL_VELOCITY {256.f, 256.f * std::cos(M_PI / 6.f)}

class ElasticBall :
    public IGameObject
{
public:
    ElasticBall(const sf::Vector2u& center, float size = 5);

    virtual void Update(const sf::Time& deltaTime) override;

protected:
    static sf::RectangleShape* CreateShape(float size);

private:
    sf::Vector2f _velocity;
};

