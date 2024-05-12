#pragma once
#include "AgentUCB.hpp"
#include "IEnviroment.hpp"
#include "TheGameOfPong/IPlayer.hpp"

class PlayerUCB
    : public IPlayer
{
public:
    PlayerUCB(const PlayerSide playerSide, const sf::Vector2f& paddleSize, const IEnviroment& enviroment);

	virtual void Update(const sf::Time& deltaTime) override;

    virtual void Reset(void) override;

    virtual void UpdateScore(Reward reward) override;
};