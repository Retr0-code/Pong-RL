#include <string>
#include <sstream>
#include <iostream>

#include "IPlayer.hpp"
#include "Scoreboard.hpp"

Scoreboard::Scoreboard(const sf::Vector2u& field, IPlayerShared leftPlayer, IPlayerShared rightPlayer)
    : IGameObject(sf::Vector2f{field.x / 2, 0}, CreateText(field)),
    _leftPlayer(leftPlayer), _rightPlayer(rightPlayer) {  }

void Scoreboard::Reset(void)
{
    sf::Text& sfText{reinterpret_cast<sf::Text&>(IGameObject::_shape->Get())};
    sfText.setString("0 : 0");
    _leftPlayer->Reset();
    _rightPlayer->Reset();
}

void Scoreboard::Update(const sf::Time &deltaTime)
{
    sf::Text& sfText{reinterpret_cast<sf::Text&>(IGameObject::_shape->Get())};
    sfText.setString(FormatValues());
}

IDrawable *Scoreboard::CreateText(const sf::Vector2u &field)
{
    return new DrawableText(std::max(field.y / 8, uint32_t(50)));
}

std::string Scoreboard::FormatValues(void)
{
    std::stringstream scoreboard;
    scoreboard << _leftPlayer->GetScore() << " : " << _rightPlayer->GetScore();
    return scoreboard.str();
}
