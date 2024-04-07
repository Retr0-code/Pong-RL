#include "ElasticBall.hpp"
#include "TheGameOfPong.hpp"

ElasticBall::ElasticBall(const sf::Vector2u& center, float size)
    : IGameObject(CreateShape(size), sf::Vector2f(center)), _velocity(ELASTICBALL_VELOCITY) {  }

void ElasticBall::Update(const sf::Time& deltaTime)
{
    sf::Vector2f position{IGameObject::_shape->getPosition()};
    if (position.y > TheGameOfPong::Field().y || position.y < 0)
        _velocity.y = -_velocity.y;

    if (position.x > TheGameOfPong::Field().x || position.x < 0)
        _velocity.x = -_velocity.x;

    IGameObject::_shape->move(_velocity * deltaTime.asSeconds());
}

sf::RectangleShape *ElasticBall::CreateShape(float size)
{
    return new sf::RectangleShape({size, size});
}
