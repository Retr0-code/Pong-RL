#pragma once

#include "IPlayer.hpp"

class PlayerHuman :
    public IPlayer
{
public:
    PlayerHuman(PlayerSide playerSide, const sf::Vector2f& paddleSize);

    void Update(void) override;

    void Reset(void) override;
};
