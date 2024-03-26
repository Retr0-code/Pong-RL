#pragma once
#include "IGameObject.hpp"

class ElasticBall :
    public IGameObject
{

private:
    sf::Vector2f _velocity;
};

