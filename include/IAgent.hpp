#pragma once
#include <vector>
#include <cstdint>

template <typename T, typename ActionsEnum>
class IAgent
{
public:
    using ActionsSpace = std::vector<ActionsEnum>;
    using StateDimensions = std::vector<std::pair<T, T>>;

    virtual ActionsEnum Action(void) = 0;

    virtual void Observe(const std::vector<T>& observation) = 0;

    virtual void Reward(float reward = 1.f) = 0;

    virtual ~IAgent() = default;

protected:
    float _totalReward;
};
