#pragma once

#include "IGameObject.hpp"

class IPlayer;

class Scoreboard
    : public IGameObject
{
public:
    using IPlayerShared = std::shared_ptr<IPlayer>;

    Scoreboard(const sf::Vector2u& field, IPlayerShared leftPlayer, IPlayerShared rightPlayer);

    virtual void Reset(void) override;

    virtual void Update(const sf::Time& deltaTime) override;

private:
    static IDrawable* CreateText(const sf::Vector2u& field);

    std::string FormatValues(void);

private:
    IPlayerShared _leftPlayer;
    IPlayerShared _rightPlayer;
};