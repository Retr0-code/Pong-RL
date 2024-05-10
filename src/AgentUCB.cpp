#include "AgentUCB.hpp"

template<typename ActionsEnum>
AgentUCB<ActionsEnum>::AgentUCB(const StateDimensions &dimensions, const ActionsSpace &actions, size_t epsilon)
    : _epsilon(epsilon), _actions(actions) {  }