#pragma once
#include <cmath>
#include <memory>

#include "IGameObject.hpp"

class IPlayer;

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#define ELASTICBALL_VELOCITY {256.f, 256.f * std::sin(M_PI / 12.f)}

/**
 * @brief Ball class simulating elastic hit with players and borders
 */
class ElasticBall :
    public IGameObject
{
public:
    /**
     * @brief alias for std::shared_ptr<IPlayer>
     */
    using IPlayerShared = std::shared_ptr<IPlayer>;

    /**
     * @brief Construct a new ElasticBall object
     * 
     * @param center position of game-field center
     * @param size diameter of the ball
     */
    ElasticBall(const sf::Vector2u& center, float size = 10);

    /**
     * @brief Set the players object
     * 
     * @param leftPlayer 
     * @param rightPlayer 
     */
    virtual void SetPlayers(IPlayerShared leftPlayer, IPlayerShared rightPlayer);

    /**
     * @brief Resets velocity vector and position
     */
    virtual void Reset(void) override;

    /**
     * @brief `GameEngine` update function
     * 
     * @param deltaTime time between frames
     */
    virtual void Update(const sf::Time& deltaTime) override;

    /**
     * @brief Getter for velocity vector
     * 
     * @return const sf::Vector2f& velocity
     */
    virtual const sf::Vector2f& GetVelocity(void);

    /**
     * @brief Getter the Velocity Limit vector
     * 
     * @return sf::Vector2f& `ElasticBall::_velocityLimit`
     */
    static sf::Vector2f& GetVelocityLimit(void);

protected:
    /**
     * @brief Create a Shape object
     * 
     * @param size diameter
     * @return DrawableRect* newly created ball object on a heap
     */
    static DrawableRect* CreateShape(float size);

private:
    void UpdatePlayersScore(IPlayerShared scoredPlayer, IPlayerShared missedPlayer);

    sf::Vector2f _velocity;
    sf::Vector2f _velocityDefault;
    IPlayerShared _leftPlayer;
    IPlayerShared _rightPlayer;
    static sf::Vector2f _velocityLimit;
};
