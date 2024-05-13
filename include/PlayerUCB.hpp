#pragma once
#include "AgentUCB.hpp"
#include "EnviromentPong.hpp"
#include "TheGameOfPong/IPlayer.hpp"

class PlayerUCB
    : public IPlayer
{
public:
    PlayerUCB(const PlayerSide playerSide, const sf::Vector2f& paddleSize);

    void CreateAgent(const EnviromentPong& enviroment);

	virtual void Update(const sf::Time& deltaTime) override;

    virtual void Reset(void) override;

    virtual void UpdateScore(Reward reward) override;

private:
    std::vector<float> Observation(void) const;

private:
    std::unique_ptr<AgentUCB<IPlayer::PlayerAction>> _agent;
};