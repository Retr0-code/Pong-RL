#pragma once

#include "IGameObject.hpp"

class IPlayer;

class Scoreboard
    : public IGameObject
{
public:
    Scoreboard(const IPlayer& leftPlayer, const IPlayer& rightPlayer);

    virtual void Reset(void);

    virtual void Update(sf::Time deltaTime);
};