#include <cmath>
#include <limits>
#include <random>
#include <stdexcept>

#include "AgentUCB.hpp"

template<typename ActionsEnum>
AgentUCB<ActionsEnum>::AgentUCB(const StateDimensions &dimensions, const ActionsSpace &actions, float epsilon, float rewardRatio)
    : _inputsAmount(dimensions.size()), _epsilon(epsilon),
    _actions(actions), _rewardRatio(rewardRatio), _episode(0)
{
    size_t totalSize{1};
    for (auto& borders : dimensions)
        totalSize *= std::abs(borders.first * borders.second);

    _states.reserve(totalSize);
}

template <typename ActionsEnum>
ActionsEnum &AgentUCB<ActionsEnum>::Action(void)
{
    if (_epsilon == 0.0)
        return UCB();

    // Inititialize with last action in vector
    ActionsEnum action{*(_actions.end() - 1)};

    std::default_random_engine rng;
    std::uniform_real_distribution<float> actionChoice(0.f, _epsilon);
    if (_epsilon >= actionChoice(rng))
    {
        std::uniform_real_distribution<float> randomAction(0.f, 1.f);
        float action{randomAction(rng)};
        
        for (size_t index{1}; index < _actions.size(); ++index)
        {
            if (randomAction <= float(index) / _actions.size())
                action = _actions[index];
        }
    }
    ++_lastObservationState.actionsStats[action].timesSelected;

    return action;
}

template <typename ActionsEnum>
const std::vector<float> &AgentUCB<ActionsEnum>::Observe(const std::vector<float> &observation)
{
    if (observation.size() != _inputsAmount)
        throw std::invalid_argument{"Error in [const std::vector<float> &AgentUCB<ActionsEnum>::Observe(const std::vector<float> &observation)]:\n\tobservation does not math size of inputs."};
    
    if (!_states.contains(observation))
        throw std::invalid_argument{"Error in [const std::vector<float> &AgentUCB<ActionsEnum>::Observe(const std::vector<float> &observation)]:\n\tobservation does not exist."};

    _lastObservationState = _states[observation];
}

template <typename ActionsEnum>
void AgentUCB<ActionsEnum>::Reward(bool positive)
{

}

template <typename ActionsEnum>
ActionsEnum& AgentUCB<ActionsEnum>::UCB(void)
{
    ActionsEnum selectedAction{_actions[0]};
    float maxUpperBound{0};
    for (auto& [action, actionStats] : _lastObservationState.actionsStats)
    {
        
        if (actionStats.timesSelected == 0)
            actionStats.upperBound = std::numeric_limits<float>::infinity();
        else
        {
            float rewardAvg{actionStats.rewardSum / actionStats.timesSelected};
            actionStats.upperBound = rewardAvg + std::sqrt(3.f / 2.f * std::log(_episode + 1) / actionStats.timesSelected);
        }

        if (maxUpperBound < actionStats.upperBound)
        {
            selectedAction = action;
            maxUpperBound = actionStats.upperBound;
        }
    }

    return selectedAction;
}

template <typename ActionsEnum>
float AgentUCB<ActionsEnum>::NextReward(StateActionReward& state)
{
    return state.nextReward = state.nextReward * _rewardRatio;
}
