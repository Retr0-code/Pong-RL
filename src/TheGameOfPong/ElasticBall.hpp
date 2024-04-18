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
    using IPlayerShared = std::shared_ptr<IPlayer>;

    ElasticBall(const sf::Vector2u& center, float size = 10);

    virtual void SetPlayers(IPlayerShared leftPlayer, IPlayerShared rightPlayer);

    virtual void Reset(void) override;

    virtual void Update(const sf::Time& deltaTime) override;

protected:
    static DrawableRect* CreateShape(float size);

private:
    void UpdatePlayersScore(IPlayerShared scoredPlayer, IPlayerShared missedPlayer);

    sf::Vector2f _velocity;
    sf::Vector2f _velocityDefault;
    IPlayerShared _leftPlayer;
    IPlayerShared _rightPlayer;
};

