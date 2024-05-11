#include <stdexcept>

#include "AgentUCB.hpp"

template<typename ActionsEnum>
AgentUCB<ActionsEnum>::AgentUCB(const StateDimensions &dimensions, const ActionsSpace &actions, float epsilon)
    : _inputsAmount(dimensions.size()), _epsilon(epsilon), _actions(actions)
{
    size_t totalSize{1};
    for (auto& borders : dimensions)
        totalSize *= std::abs(borders.first * borders.second);

    _states.reserve(totalSize);
}

template <typename ActionsEnum>
const std::vector<float> &AgentUCB<ActionsEnum>::Observe(const std::vector<float> &observation)
{
    if (observation.size() != _inputsAmount)
        throw std::invalid_argument{"Error in [const std::vector<float> &AgentUCB<ActionsEnum>::Observe(const std::vector<float> &observation)]:\n\tobservation does not math size of inputs."};
    
    
}
