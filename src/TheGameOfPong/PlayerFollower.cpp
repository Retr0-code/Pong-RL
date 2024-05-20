#include "ElasticBall.hpp"
#include "TheGameOfPong.hpp"
#include "PlayerFollower.hpp"

PlayerFollower::PlayerFollower(PlayerSide playerSide, const sf::Vector2f &paddleSize)
    : IPlayer(playerSide, paddleSize) {  }

void PlayerFollower::Update(const sf::Time &deltaTime)
{
    sf::RectangleShape& ballShape{reinterpret_cast<sf::RectangleShape&>(_ball->Shape()->Get())};
    sf::RectangleShape& playerShape{reinterpret_cast<sf::RectangleShape&>(_shape->Get())};
    sf::FloatRect playerHitbox{playerShape.getGlobalBounds()};

    PlayerAction direction{PlayerAction::Stay};
    bool ballDirection{_ball->GetVelocity().x > 0};
    bool playerSide{playerHitbox.left > TheGameOfPong::Field().x / 2};

    if (ballShape.getPosition().y > playerHitbox.top + playerHitbox.height && ballDirection == playerSide)
        direction = Down;

    else if (ballShape.getPosition().y < playerHitbox.top && ballDirection == playerSide)
        direction = Up;

    UpdateVelocity(direction, deltaTime);
}

void PlayerFollower::Reset(void)
{
    IPlayer::Reset();
    _score = 0;
}

void PlayerFollower::UpdateScore(Reward reward)
{
    _score += reward;
}
