#include "PlayerHuman.hpp"

PlayerHuman::PlayerHuman(PlayerSide playerSide, const sf::Vector2f &paddleSize)
    : IPlayer(playerSide, paddleSize) {  }

void PlayerHuman::Update(void)
{
}

void PlayerHuman::Reset(void)
{
    IGameObject::Reset();
    _score = 0;
    _velocity = 0;
}
