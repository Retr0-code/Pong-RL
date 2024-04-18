#pragma once
#include "IGameObject.hpp"

class ElasticBall;

/** \class IPlayer
*   \brief Class provides interface for player entities in the game of pong.
*/
class IPlayer :
    public IGameObject
{
public:
    typedef enum
    {
        Left,
        Right
    } PlayerSide;

    typedef enum
    {
        Stay = 0,
        Up = -1,
        Down = 1
    } PlayerAction;

    typedef enum
    {
        Miss = 0,
        Score = 1
    } Reward;

    IPlayer(const PlayerSide playerSide, const sf::Vector2f& paddleSize);
    
    virtual void Reset(void) override;

    static void SetVelocityLimit(const float velocity);

    virtual float GetVelocityLimit(void) const;

    virtual float GetCurrentVelocity(void) const;
    
    virtual uint16_t GetScore(void) const;

    virtual void SetOtherPlayer(std::shared_ptr<IPlayer> otherPlayer);

    virtual void SetBall(std::shared_ptr<ElasticBall> ball);

    virtual void UpdateScore(Reward reward) = 0;

    virtual ~IPlayer() = default;

protected:
    static DrawableRect* CreateShape(const sf::Vector2f& size);

    static sf::Vector2f ChooseSide(const PlayerSide side);

protected:
    uint16_t _score;
    float _currentVelocity;
    std::shared_ptr<IPlayer> _otherPlayer;
    std::shared_ptr<ElasticBall> _ball;

private:
    static sf::Vector2f _playerSize;
    static float _velocityLimit;
    static float _acceleration;
};
