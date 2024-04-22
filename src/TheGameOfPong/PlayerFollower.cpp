#include <iostream>

#include "ElasticBall.hpp"
#include "PlayerFollower.hpp"

PlayerFollower::PlayerFollower(PlayerSide playerSide, const sf::Vector2f &paddleSize)
    : IPlayer(playerSide, paddleSize) {  }

void PlayerFollower::Update(const sf::Time &deltaTime)
{
    sf::RectangleShape& ballShape{reinterpret_cast<sf::RectangleShape&>(_ball->Shape()->Get())};
    sf::RectangleShape& playerShape{reinterpret_cast<sf::RectangleShape&>(_shape->Get())};
    sf::FloatRect playerHitbox{playerShape.getGlobalBounds()};

    PlayerAction direction{PlayerAction::Stay};
    if (ballShape.getPosition().y > playerHitbox.top + playerHitbox.height)
        direction = Down;

    else if (ballShape.getPosition().y < playerHitbox.top)
        direction = Up;

    UpdateVelocity(direction);
    playerShape.move(0, GetVelocityLimit() * direction * deltaTime.asSeconds());
}

void PlayerFollower::UpdateScore(Reward reward)
{
    _score += reward;
}
