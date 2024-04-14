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

float IPlayer::GetVelocityLimit(void) const
{
	return _velocityLimit;
}

float IPlayer::GetCurrentVelocity(void) const
{
    return _currentVelocity;
}

void IPlayer::SetOtherPlayer(std::shared_ptr<IPlayer> otherPlayer)
{
	if (otherPlayer.get() == nullptr)
		throw std::invalid_argument{ "Error: IPlayer::SetOtherPlayer got nullptr." };

	_otherPlayer = otherPlayer;
}

void IPlayer::SetBall(std::shared_ptr<ElasticBall> ball)
{
	if (ball.get() == nullptr)
		throw std::invalid_argument{ "Error: IPlayer::SetBall got nullptr." };
		
	_ball = ball;
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
