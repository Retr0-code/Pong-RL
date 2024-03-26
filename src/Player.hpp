#pragma once
#include "IGameObject.hpp"

class Player :
    public IGameObject
{
private:
    uint16_t _score;
    static float _velocity;
};

