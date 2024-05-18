#pragma once
#include "AgentUCB.hpp"
#include "EnviromentPong.hpp"
#include "TheGameOfPong/IPlayer.hpp"

class PlayerUCB
    : public IPlayer
{
public:
    using AgentPtr = std::shared_ptr<AgentUCB<IPlayer::PlayerAction>>;

    PlayerUCB(const PlayerSide playerSide, const sf::Vector2f& paddleSize);

    void CreateAgent(const EnvironmentPong& enviroment);

	virtual void Update(const sf::Time& deltaTime) override;

    virtual void Reset(void) override;

    virtual void UpdateScore(Reward reward) override;

    virtual void SetEpsilon(float epsilon);

    virtual const AgentPtr& Agent(void);

private:
    std::vector<float> Observation(void) const;

private:
    AgentPtr _agent;
};