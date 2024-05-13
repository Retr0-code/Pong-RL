#pragma once
#include "IPlayer.hpp"
#include "IEnviroment.hpp"
#include "TheGameOfPong.hpp"

class EnviromentPong
    : public IEnviroment<IPlayer::PlayerAction, int64_t>
{
public:
    using StateDimensions = std::vector<std::pair<int64_t, int64_t>>;

    EnviromentPong(void);
};
