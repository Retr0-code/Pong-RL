#pragma once
#include <vector>
#include <cstdint>

template <typename T, typename ActionsEnum>
class IAgent
{
public:
    using ActionsSpace = std::vector<ActionsEnum>;
    using StateDimensions = std::vector<std::pair<T, T>>;

    virtual T Reward(void) = 0;

    virtual const ActionsEnum& Action(void) const = 0;

    virtual const std::vector<T>& Observe(const std::vector<T>& observation) = 0;

    virtual ~IAgent() = default;
};
