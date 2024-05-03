#include <iostream>
#include "ElasticBall.hpp"
#include "TheGameOfPong.hpp"

ElasticBall::ElasticBall(const sf::Vector2u& center, float size)
    : IGameObject(sf::Vector2f(center), CreateShape(size)),
    _velocity(ELASTICBALL_VELOCITY), _velocityDefault(_velocity) {  }

void ElasticBall::SetPlayers(IPlayerShared leftPlayer, IPlayerShared rightPlayer)
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

    if (position.x < 0)
        UpdatePlayersScore(_rightPlayer, _leftPlayer);

    else if (position.x > TheGameOfPong::Field().x)
        UpdatePlayersScore(_leftPlayer, _rightPlayer);

    IPlayer* _player{nullptr};
    if (shape.getGlobalBounds().intersects(shapePlayerLeft.getGlobalBounds()))
        _player = _leftPlayer.get();
    
    else if (shape.getGlobalBounds().intersects(shapePlayerRight.getGlobalBounds()))
        _player = _rightPlayer.get();
    
    if (_player)
    {
        _velocity.x = -_velocity.x;
        _velocity.y = std::clamp(_velocity.y + _player->GetCurrentVelocity() * 256.f, -512.f, 512.f);
    }

    shape.move(_velocity * deltaTime.asSeconds());
}

const sf::Vector2f &ElasticBall::GetVelocity(void)
{
    return _velocity;
}

DrawableRect *ElasticBall::CreateShape(float size)
{
    return new DrawableRect({size, size});
}

void ElasticBall::UpdatePlayersScore(IPlayerShared scoredPlayer, IPlayerShared missedPlayer)
{
    scoredPlayer->UpdateScore(IPlayer::Reward::Score);
    missedPlayer->UpdateScore(IPlayer::Reward::Miss);

    this->Reset();
    _leftPlayer->IPlayer::Reset();
    _rightPlayer->IPlayer::Reset();
}
