#include "IPlayer.hpp"
#include "TheGameOfPong.hpp"

float IPlayer::_velocityLimit{ 256.f };
sf::Vector2f IPlayer::_playerSize{ 5, 30 };
float IPlayer::_acceleration{ 0.05f };

IPlayer::IPlayer(const PlayerSide playerSide, const sf::Vector2f& paddleSize)
	: IGameObject(ChooseSide(playerSide), CreateShape(paddleSize)),
	_score(0), _currentVelocity(0.f) {  }

void IPlayer::Reset(void)
{
	IGameObject::Reset();
	_currentVelocity = 0;
}

void IPlayer::SetVelocityLimit(const float velocity)
{
	if (velocity <= 0)
		throw std::invalid_argument{ "Error: IPlayer::SetVelocityLimit velocity cannot be less or equal to zero." };

	_velocityLimit = velocity;
}

float IPlayer::GetVelocityLimit(void)
{
	return _velocityLimit;
}

float IPlayer::GetCurrentVelocity(void) const
{
    return _currentVelocity;
}

uint16_t IPlayer::GetScore(void) const
{
    return _score;
}

void IPlayer::SetOtherPlayer(std::shared_ptr<IPlayer> otherPlayer)
{
	if (otherPlayer.get() == nullptr)
		throw std::invalid_argument{ "Error: IPlayer::SetOtherPlayer got nullptr." };

	if (otherPlayer.get() == this)
		throw std::invalid_argument{ "Error: IPlayer::SetOtherPlayer got pointer to itself." };

	_otherPlayer = otherPlayer;
}

void IPlayer::SetBall(std::shared_ptr<ElasticBall> ball)
{
	if (ball.get() == nullptr)
		throw std::invalid_argument{ "Error: IPlayer::SetBall got nullptr." };
		
	_ball = ball;
}

void IPlayer::UpdateVelocity(PlayerAction action, sf::Time deltaTime)
{
	switch (action)
	{
		case Up:
    		_currentVelocity -= 1 >= std::abs(_currentVelocity) ? _acceleration : 0;
			break;
		case Down:
    		_currentVelocity += 1 >= std::abs(_currentVelocity) ? _acceleration : 0;
			break;
		default:
        	_currentVelocity *= _acceleration;
	}
    reinterpret_cast<sf::Shape&>(_shape->Get()).move(
		0, GetVelocityLimit() * deltaTime.asSeconds() * TheGameOfPong::GetSpeedMultiplier() * action
	);
}

DrawableRect *IPlayer::CreateShape(const sf::Vector2f &size)
{
	_playerSize = size;
    return new DrawableRect(_playerSize);
}

sf::Vector2f IPlayer::ChooseSide(const PlayerSide side)
{
	sf::Vector2f field{ TheGameOfPong::Field() };
	field.y /= 2;
	field.x = side == Right ? field.x - _playerSize.x * 2 : _playerSize.x;
    return field;
}
