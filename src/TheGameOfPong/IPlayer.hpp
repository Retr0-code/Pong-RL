#pragma once
#include "IGameObject.hpp"

/** \class IPlayer
*   \brief Class provides interface for player entities in the game of pong.
*/
class IPlayer :
    public IGameObject
{
public:
    typedef enum PlayerSide
    {
        Left,
        Right
    };

    IPlayer(PlayerSide playerSide, const sf::Vector2f& paddleSize);

    virtual void Update(void) = 0;

    void SetVelocityLimit(float velocity);

    float GetVelocityLimit(float velocity) const;

    virtual ~IPlayer(void) = default;

private:
    static sf::RectangleShape* CreateShape(void);

protected:
    uint16_t _score;
    float _velocity;

private:
    static float _velocityLimit;
};
