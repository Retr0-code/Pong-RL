#include "PlayerUCB.hpp"

PlayerUCB::PlayerUCB(const PlayerSide playerSide, const sf::Vector2f &paddleSize)
    : IPlayer(playerSide, paddleSize) {  }

void PlayerUCB::CreateAgent(const EnviromentPong &enviroment)
{
    _agent = std::make_unique<AgentUCB<IPlayer::PlayerAction>>(enviroment.States(), enviroment.ActionSpace(), 0.07f, 0.96);
}

void PlayerUCB::Update(const sf::Time &deltaTime)
{
    sf::RectangleShape& shape{reinterpret_cast<sf::RectangleShape&>(IGameObject::_shape->Get())};
    sf::RectangleShape& ballShape{reinterpret_cast<sf::RectangleShape&>(_ball->Shape()->Get())};
    sf::FloatRect paddleHitbox{shape.getGlobalBounds()};

    _agent->Observe(Observation());
    PlayerAction direction{_agent->Action()};

    if (!(TheGameOfPong::FieldRect().contains({shape.getPosition().x, paddleHitbox.top})
    && TheGameOfPong::FieldRect().contains({shape.getPosition().x, paddleHitbox.top + paddleHitbox.height})))
        direction = PlayerAction::Stay;

    if (shape.getGlobalBounds().intersects(ballShape.getGlobalBounds()))
        _agent->Reward(1.f);
    
    UpdateVelocity(direction, deltaTime);
}

void PlayerUCB::Reset(void)
{
    IPlayer::Reset();
    _score = 0;
}

void PlayerUCB::UpdateScore(Reward reward)
{
    _score += reward;
    _agent->Reward(2.f * (reward == Reward::Score));
}

void PlayerUCB::SetEpsilon(float epsilon)
{
    _agent->SetEpsilon(epsilon);
}

std::vector<float> PlayerUCB::Observation(void) const
{
    sf::RectangleShape& ballShape{reinterpret_cast<sf::RectangleShape&>(_ball->Shape()->Get())};
    sf::RectangleShape& playerShape{reinterpret_cast<sf::RectangleShape&>(_shape->Get())};
    sf::Vector2f ballPosition{ballShape.getPosition()};
    sf::Vector2f playerPosition{playerShape.getPosition()};
    const sf::Vector2f& ballVelocity{_ball->GetVelocity()};

    return {
        ballPosition.x,
        ballPosition.y,
        playerPosition.y,
        ballVelocity.x > 0 ? AgentUCB<IPlayer::PlayerAction>::Sampling() : -AgentUCB<IPlayer::PlayerAction>::Sampling(),
        ballVelocity.y / ballVelocity.x
    };
}
