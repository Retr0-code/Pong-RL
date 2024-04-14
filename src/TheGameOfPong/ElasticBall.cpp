#include <iostream>
#include "ElasticBall.hpp"
#include "TheGameOfPong.hpp"

ElasticBall::ElasticBall(const sf::Vector2u& center, float size)
    : IGameObject(sf::Vector2f(center), CreateShape(size)),
    _velocity(ELASTICBALL_VELOCITY), _velocityDefault(_velocity) {  }

void ElasticBall::SetPlayers(std::shared_ptr<IPlayer> leftPlayer, std::shared_ptr<IPlayer> rightPlayer)
{
    if (leftPlayer.get() == nullptr || rightPlayer.get() == nullptr)
		throw std::invalid_argument{ "Error: ElasticBall::SetPlayers got nullptr." };

    _leftPlayer = leftPlayer;
    _rightPlayer = rightPlayer;
}

void ElasticBall::Reset(void)
{
    IGameObject::Reset();
    _velocity.y = _velocityDefault.y;
}

void ElasticBall::Update(const sf::Time& deltaTime)
{
    sf::RectangleShape& shape = reinterpret_cast<sf::RectangleShape&>(IGameObject::_shape->Get());
    sf::RectangleShape& shapePlayerLeft = reinterpret_cast<sf::RectangleShape&>(_leftPlayer->Shape()->Get());
    sf::RectangleShape& shapePlayerRight = reinterpret_cast<sf::RectangleShape&>(_rightPlayer->Shape()->Get());
    sf::Vector2f position{shape.getPosition()};

    if (position.y > TheGameOfPong::Field().y || position.y < 0)
        _velocity.y = -_velocity.y;

    if (position.x > TheGameOfPong::Field().x || position.x < 0)
    {
        this->Reset();
        _leftPlayer->Reset();
        _rightPlayer->Reset();
    }

    IPlayer* _playerCollided{nullptr};
    if (shape.getGlobalBounds().intersects(shapePlayerLeft.getGlobalBounds()))
        _playerCollided = _leftPlayer.get();
    
    else if (shape.getGlobalBounds().intersects(shapePlayerRight.getGlobalBounds()))
        _playerCollided = _rightPlayer.get();
    
    if (_playerCollided)
    {
        _velocity.x = -_velocity.x;
        _velocity.y = std::clamp(_velocity.y + _playerCollided->GetCurrentVelocity() * 256.f, -512.f, 512.f);
    }

    shape.move(_velocity * deltaTime.asSeconds());
}

DrawableRect *ElasticBall::CreateShape(float size)
{
    return new DrawableRect({size, size});
}
