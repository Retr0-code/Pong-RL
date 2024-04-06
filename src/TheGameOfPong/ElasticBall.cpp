#include "ElasticBall.hpp"

ElasticBall::ElasticBall(const sf::Vector2u& center, float size)
    : IGameObject(CreateShape(size), sf::Vector2f(center)) {  }

sf::RectangleShape *ElasticBall::CreateShape(float size)
{
    return new sf::RectangleShape({size, size});
}
