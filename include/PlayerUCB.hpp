#pragma once
#include "AgentUCB.hpp"
#include "EnviromentPong.hpp"
#include "TheGameOfPong/IPlayer.hpp"

/**
 * @brief The game of pong player controlled by RL agent
 */
class PlayerUCB
    : public IPlayer
{
public:
    /**
     * @brief alias for std::shared_ptr<AgentUCB<IPlayer::PlayerAction>>
     */
    using AgentPtr = std::shared_ptr<AgentUCB<IPlayer::PlayerAction>>;
    /**
     * @brief alias for IEnvironment<IPlayer::PlayerAction, int64_t>
     */
    using EnvironmentPong = IEnvironment<IPlayer::PlayerAction, int64_t>;

    /**
     * @brief Construct a new Player U C B object
     * 
     * @param playerSide assigns players side
     * @param paddleSize assigns static paddleSize
     */
    PlayerUCB(const PlayerSide playerSide, const sf::Vector2f& paddleSize);

    /**
     * @brief Create an RL agent
     * 
     * @param enviroment object of EnvironmentPong5/3I
     */
    void CreateAgent(const EnvironmentPong& enviroment);

    /**
     * @brief `GameEngine` update function
     * 
     * @param deltaTime time between ticks or frames
     */
	virtual void Update(const sf::Time& deltaTime) override;

    /**
     * @brief Reset player and agent to the original state
     */
    virtual void Reset(void) override;

    /**
     * @brief Updates score with agents reward
     * 
     * @param reward value of reward
     */
    virtual void UpdateScore(Reward reward) override;

    /**
     * @brief Set the Epsilon ratio
     * 
     * @param epsilon new eps
     */
    virtual void SetEpsilon(float epsilon);

    /**
     * @brief Getter of agent object
     * 
     * @return const AgentPtr& `PlayerUCB::_agent`
     */
    virtual const AgentPtr& Agent(void);

private:
    std::vector<float> Observation(void) const;

private:
    AgentPtr _agent;
    size_t _observationSize;
};
