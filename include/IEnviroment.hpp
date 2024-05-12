#pragma once
#include <vector>

template <typename ActionsEnum>
class IEnviroment
{
public:
    const std::vector<ActionsEnum>& ActionSpace(void) const;

    std::vector<float> Observation(void) const;

protected:
    std::vector<ActionsEnum> _actionSpace;
};
