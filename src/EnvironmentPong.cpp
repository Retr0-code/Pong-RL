#include "AgentUCB.hpp"
#include "EnviromentPong.hpp"

EnvironmentPong5I::EnvironmentPong5I(void)
{
    _actionSpace = {
        IPlayer::PlayerAction::Down,
        IPlayer::PlayerAction::Stay,
        IPlayer::PlayerAction::Up
    };

    _states = {
        {0, TheGameOfPong::Field().x}, // Ball's position changes from 0 to TheGameOfPong::Field().x
        {0, TheGameOfPong::Field().y}, // Ball's position changes from 0 to TheGameOfPong::Field().y
        {0, TheGameOfPong::Field().y}, // Paddle's position changes from 0 to TheGameOfPong::Field().y
        {-int64_t(AgentUCB<IPlayer::PlayerAction>::Sampling()),
            AgentUCB<IPlayer::PlayerAction>::Sampling()
        },    // Ball's X velocity changes only direction
        {-ElasticBall::GetVelocityLimit().y / ElasticBall::GetVelocityLimit().x,
            ElasticBall::GetVelocityLimit().y / ElasticBall::GetVelocityLimit().x
        } // Ball's Y velocity changes from -y to y
    };
}


EnvironmentPong3I::EnvironmentPong3I(void)
{
    _actionSpace = {
        IPlayer::PlayerAction::Down,
        IPlayer::PlayerAction::Stay,
        IPlayer::PlayerAction::Up
    };

    _states = {
        {0, TheGameOfPong::Field().y}, // Paddle's position changes from 0 to TheGameOfPong::Field().y
        {-int64_t(AgentUCB<IPlayer::PlayerAction>::Sampling()),
            AgentUCB<IPlayer::PlayerAction>::Sampling()
        },    // Ball's X velocity changes only direction
        {-ElasticBall::GetVelocityLimit().y / ElasticBall::GetVelocityLimit().x,
            ElasticBall::GetVelocityLimit().y / ElasticBall::GetVelocityLimit().x
        } // Ball's Y velocity changes from -y to y
    };
}
