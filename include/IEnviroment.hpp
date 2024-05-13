#pragma once
#include <vector>

template <typename ActionsEnum, typename T>
class IEnviroment
{
public:
    using StateDimensions = std::vector<std::pair<T, T>>;

    const std::vector<ActionsEnum>& ActionSpace(void) const
    {
        return _actionSpace;
    }

    virtual const StateDimensions& States(void) const
    {
        return _states;
    }

protected:
    StateDimensions _states;
    std::vector<ActionsEnum> _actionSpace;
};
