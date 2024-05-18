#pragma once
#include <vector>

template <typename ActionsEnum, typename T>
class IEnvironment
{
public:
    using ActionsSpace = std::set<ActionsEnum>;
    using StateDimensions = std::vector<std::pair<T, T>>;

    const ActionsSpace& ActionSpace(void) const
    {
        return _actionSpace;
    }

    virtual const StateDimensions& States(void) const
    {
        return _states;
    }

protected:
    StateDimensions _states;
    ActionsSpace _actionSpace;
};
