#include "IPlayer.hpp"

float IPlayer::_velocityLimit{ 0 };


IPlayer::IPlayer(PlayerSide playerSide)
	: IGameObject({0,0}, CreateShape())
{
}

void IPlayer::SetVelocityLimit(float velocity)
{
	if (velocity <= 0)
		throw std::exception{ "Error: IPlayer::SetVelocityLimit velocity cannot be less or equal to zero." };

	_velocityLimit = velocity;
}

float IPlayer::GetVelocityLimit(float velocity) const
{
	return _velocityLimit;
}

