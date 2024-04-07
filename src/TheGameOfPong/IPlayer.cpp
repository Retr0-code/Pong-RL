#include "IPlayer.hpp"
#include "TheGameOfPong.hpp"

float IPlayer::_velocityLimit{ 0.4f };
sf::Vector2f IPlayer::_playerSize{ 5, 30 };

IPlayer::IPlayer(const PlayerSide playerSide, const sf::Vector2f& paddleSize)
	: IGameObject(CreateShape(paddleSize), ChooseSide(playerSide)) {  }

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

sf::RectangleShape *IPlayer::CreateShape(const sf::Vector2f &size)
{
	_playerSize = size;
    return new sf::RectangleShape(_playerSize);
}

sf::Vector2f IPlayer::ChooseSide(const PlayerSide side)
{
	sf::Vector2f field{ TheGameOfPong::Field() };
	field.y /= 2;
	field.x = side == Right ? field.x - _playerSize.x - _playerSize.x / 2 : _playerSize.x;
    return field;
}
