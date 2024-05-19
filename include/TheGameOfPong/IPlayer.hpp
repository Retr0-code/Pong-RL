#pragma once
#include "IGameObject.hpp"

class ElasticBall;

/**
 * @brief Class provides interface for player entities in the game of pong
 */
class IPlayer :
    public IGameObject
{
public:
    /**
     * @brief Defines players sides
     */
    typedef enum
    {
        Left,
        Right
    } PlayerSide;

    /**
     * @brief Defines set of action that will be used in movement arithmetics
     */
    typedef enum
    {
        Stay = 0,
        Up = -1,
        Down = 1
    } PlayerAction;

    /**
     * @brief Defines reward states
     */
    typedef enum
    {
        Miss = 0,
        Score = 1
    } Reward;

    /**
     * @brief Construct a new IPlayer object
     * 
     * @param playerSide assigns players side
     * @param paddleSize assigns static paddleSize
     */
    IPlayer(const PlayerSide playerSide, const sf::Vector2f& paddleSize);
    
    /**
     * @brief Resets player state
     */
    virtual void Reset(void) override;

    /**
     * @brief Setter for the static velocity limit
     * 
     * @param velocity value of velocity limit
     */
    static void SetVelocityLimit(const float velocity);

    /**
     * @brief Getter for the static velocity limit
     * 
     * @return float current velocity limit
     */
    static float GetVelocityLimit(void);

    /**
     * @brief Getter for the player's current velocity 1D vector
     * 
     * @return float current velocity vector
     */
    virtual float GetCurrentVelocity(void) const;
    
    /**
     * @brief Getter for player's score
     * 
     * @return uint16_t player's score
     */
    virtual uint16_t GetScore(void) const;

    /**
     * @brief Set the other player object
     * 
     * @param otherPlayer shared pointer to opposite player
     */
    virtual void SetOtherPlayer(std::shared_ptr<IPlayer> otherPlayer);

    /**
     * @brief Set the Ball object
     * 
     * @param ball shared pointer to ball object
     */
    virtual void SetBall(std::shared_ptr<ElasticBall> ball);

    /**
     * @brief Pure virtual function for updating player's reward
     * 
     * @param reward
     */
    virtual void UpdateScore(Reward reward) = 0;

    virtual ~IPlayer() = default;

protected:
    /**
     * @brief Create a player's shape object
     * 
     * @param size 2D float rectangle size vector 
     * @return DrawableRect* newly created drawable object
     */
    static DrawableRect* CreateShape(const sf::Vector2f& size);

    /**
     * @brief Sets position depending on player's side
     * 
     * @param side 
     * @return sf::Vector2f position depending on side
     */
    static sf::Vector2f ChooseSide(const PlayerSide side);

    /**
     * @brief Updates acceleration and current velocity
     * 
     * @param action
     * @param deltaTime time between frames
     */
    virtual void UpdateVelocity(PlayerAction action, sf::Time deltaTime);

protected:
    uint16_t _score;    // player game score
    float _currentVelocity; // current velocity 1D vector on y axis
    std::shared_ptr<IPlayer> _otherPlayer; // pointer to other player object
    std::shared_ptr<ElasticBall> _ball; // pointer to ball object

private:
    static sf::Vector2f _playerSize;
    static float _velocityLimit;
    static float _acceleration;
};
