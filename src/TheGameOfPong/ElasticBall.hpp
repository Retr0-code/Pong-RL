#pragma once
#include "IGameObject.hpp"

class ElasticBall :
    public IGameObject
{
public:
    ElasticBall(const sf::Vector2u& center, float size = 5);


protected:
    static sf::RectangleShape* CreateShape(float size);

private:
    sf::Vector2f _velocity;
};

