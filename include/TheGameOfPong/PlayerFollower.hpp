#pragma once 

#include "IPlayer.hpp"

class PlayerFollower
    : public IPlayer
{
public:
    PlayerFollower(PlayerSide playerSide, const sf::Vector2f& paddleSize);

    virtual void Update(const sf::Time& deltaTime) override;
    
    virtual void UpdateScore(Reward reward) override;
};
