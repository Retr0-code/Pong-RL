#pragma once
#include <cmath>
#include <memory>

#include "IGameObject.hpp"

class IPlayer;

#define ELASTICBALL_VELOCITY {256.f, 256.f * std::sin(M_PI / 12.f)}

class ElasticBall :
    public IGameObject
{
public:
    ElasticBall(const sf::Vector2u& center, float size = 10);

    virtual void SetPlayers(std::shared_ptr<IPlayer> leftPlayer, std::shared_ptr<IPlayer> rightPlayer);

    virtual void Reset(void) override;

    virtual void Update(const sf::Time& deltaTime) override;

protected:
    static sf::RectangleShape* CreateShape(float size);

private:
    sf::Vector2f _velocity;
    sf::Vector2f _velocityDefault;
    std::shared_ptr<IPlayer> _leftPlayer;
    std::shared_ptr<IPlayer> _rightPlayer;
};

