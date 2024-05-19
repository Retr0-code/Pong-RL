#include <iostream>
#include "PlayerUCB.hpp"

using AgentPtr = std::shared_ptr<AgentUCB<IPlayer::PlayerAction>>;

PlayerUCB::PlayerUCB(const PlayerSide playerSide, const sf::Vector2f &paddleSize)
    : IPlayer(playerSide, paddleSize), _observationSize(0) {  }

void PlayerUCB::CreateAgent(const EnvironmentPong &enviroment)
{
    _agent.reset();
    _agent = std::make_shared<AgentUCB<IPlayer::PlayerAction>>(enviroment.States(), enviroment.ActionSpace(), 0.07f, 0.95f);
    _observationSize = enviroment.States().size();
}

void PlayerUCB::Update(const sf::Time &deltaTime)
{
    sf::RectangleShape& shape{reinterpret_cast<sf::RectangleShape&>(IGameObject::_shape->Get())};
    sf::RectangleShape& ballShape{reinterpret_cast<sf::RectangleShape&>(_ball->Shape()->Get())};
    sf::FloatRect paddleHitbox{shape.getGlobalBounds()};

    _agent->Observe(Observation());
    PlayerAction direction{_agent->Action()};

    if (!TheGameOfPong::FieldRect().contains({shape.getPosition().x, paddleHitbox.top}))
        while (direction == IPlayer::Up)
            direction = _agent->Action();

    if (!TheGameOfPong::FieldRect().contains({shape.getPosition().x, paddleHitbox.top + paddleHitbox.height}))
        while (direction == IPlayer::Down)
            direction = _agent->Action();

    if (shape.getGlobalBounds().intersects(ballShape.getGlobalBounds()))
    {
        _agent->Reward(1.f);
        _agent->NextEpisode();
    }
    
    UpdateVelocity(direction, deltaTime);
}

void PlayerUCB::Reset(void)
{
    IPlayer::Reset();
    _agent->Reset();
    _score = 0;
}

void PlayerUCB::UpdateScore(Reward reward)
{
    _score += reward;
    
    _agent->Reward(2.f * reward);
    _agent->NextEpisode();
}

void PlayerUCB::SetEpsilon(float epsilon)
{
    _agent->SetEpsilon(epsilon);
}

const AgentPtr &PlayerUCB::Agent(void)
{
    return _agent;
}

std::vector<float> PlayerUCB::Observation(void) const
{
    sf::RectangleShape& ballShape{reinterpret_cast<sf::RectangleShape&>(_ball->Shape()->Get())};
    sf::RectangleShape& playerShape{reinterpret_cast<sf::RectangleShape&>(_shape->Get())};
    sf::Vector2f ballPosition{ballShape.getPosition()};
    sf::Vector2f playerPosition{playerShape.getPosition()};
    const sf::Vector2f& ballVelocity{_ball->GetVelocity()};

    std::vector<float> observation;
    switch (_observationSize)
    {
        case 3:
            observation = {
                playerPosition.y,
                ballVelocity.x > 0 ? AgentUCB<IPlayer::PlayerAction>::Sampling() : -AgentUCB<IPlayer::PlayerAction>::Sampling(),
                ballVelocity.y / ballVelocity.x
            };
            break;
        case 5:
            observation = {
                ballPosition.x,
                ballPosition.y,
                playerPosition.y,
                ballVelocity.x > 0 ? AgentUCB<IPlayer::PlayerAction>::Sampling() : -AgentUCB<IPlayer::PlayerAction>::Sampling(),
                ballVelocity.y / ballVelocity.x
            };
            break;
        default:
            throw std::runtime_error{"Error in [std::vector<float> PlayerUCB::Observation(void) const]:\n\tObservation does not match the environment."};
    }
    return observation;
}
