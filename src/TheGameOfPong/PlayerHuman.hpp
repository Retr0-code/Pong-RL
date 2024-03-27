#pragma once

#include "IPlayer.hpp"

class PlayerHuman :
    public IPlayer
{
public:
    void Update(void) override;

    void Reset(void) override;
};
