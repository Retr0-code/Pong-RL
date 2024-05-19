#pragma once 

#include "IPlayer.hpp"

/**
 * @brief Class defines simple player bot
 */
class PlayerFollower
    : public IPlayer
{
public:
    /**
     * @brief Construct a new PlayerFollower object
     * 
     * @param playerSide assigns players side
     * @param paddleSize assigns static paddleSize
     */
    PlayerFollower(PlayerSide playerSide, const sf::Vector2f& paddleSize);

    /**
     * @brief `GameEngine` update function
     * 
     * @param deltaTime time between frames
     */
    virtual void Update(const sf::Time& deltaTime) override;
    
    /**
     * @brief Total player reset
     */
    virtual void Reset(void) override;

    /**
     * @brief Score update based on reward
     * 
     * @param reward 
     */
    virtual void UpdateScore(Reward reward) override;
};
