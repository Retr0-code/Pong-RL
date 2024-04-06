#pragma once
#include "IGameObject.hpp"

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

    IPlayer(const PlayerSide playerSide, const sf::Vector2f& paddleSize);

    virtual void Update(void) = 0;

    virtual void SetVelocityLimit(const float velocity);

    virtual float GetVelocityLimit(void) const;

    virtual ~IPlayer(void) = default;

protected:
    static sf::RectangleShape* CreateShape(const sf::Vector2f& size);

    static sf::Vector2f ChooseSide(const PlayerSide side);

protected:
    uint16_t _score;
    float _velocity;

private:
    static sf::Vector2f _playerSize;
    static float _velocityLimit;
};
