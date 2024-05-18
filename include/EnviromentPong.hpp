#pragma once
#include "IPlayer.hpp"
#include "IEnviroment.hpp"
#include "TheGameOfPong.hpp"

class EnvironmentPong
    : public IEnvironment<IPlayer::PlayerAction, int64_t>
{
public:
    using ActionsSpace = std::set<IPlayer::PlayerAction>;
    using StateDimensions = std::vector<std::pair<int64_t, int64_t>>;

    EnvironmentPong(void);
};
