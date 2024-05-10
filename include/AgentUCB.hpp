#pragma once
#include <vector>
#include <unordered_map>

#include "IAgent.hpp"

// class std::hash<std::vector<float>>
// {
// public:
//     size_t operator()(const std::vector<float>& input)
//     {
//         for ()
//     }
// };

template <typename ActionsEnum>
class AgentUCB
    : public IAgent<float, ActionsEnum>
{
public:
    using ActionsSpace = std::vector<ActionsEnum>;
    using StateDimensions = std::vector<std::pair<float, float>>;

    AgentUCB(const StateDimensions& dimensions, const ActionsSpace& actions, size_t epsilon = 0);

    virtual const ActionsEnum& Action(void) const;

    const std::vector<float>& Observe(const std::vector<float>& observation);

private:
    size_t _epsilon;
    ActionsSpace _actions;
    std::unordered_map<std::vector<float>, ActionsEnum> _states;
};
