#include <cmath>
#include <limits>
#include <random>
#include <stdexcept>

#include "IPlayer.hpp"
#include "AgentUCB.hpp"

#define DEFAULT_SAMPLING 4

template<typename ActionsEnum>
size_t AgentUCB<ActionsEnum>::_sampling{DEFAULT_SAMPLING};

template<typename ActionsEnum>
AgentUCB<ActionsEnum>::StateActionReward AgentUCB<ActionsEnum>::_emptyObservationState;

template<typename ActionsEnum>
AgentUCB<ActionsEnum>::AgentUCB(const StateDimensions &dimensions, const ActionsSpace &actions, float epsilon, float rewardRatio)
    : _inputsAmount(dimensions.size()), _epsilon(epsilon),
    _actions(actions), _rewardRatio(rewardRatio),
    _episode(0), _lastObservationState(_emptyObservationState)
{
    size_t totalSize{1};
    for (auto& borders : dimensions)
        totalSize *= (std::abs(borders.first) + std::abs(borders.second)) / _sampling;

    _states.reserve(totalSize);
    _lastObservationState = _states[std::vector<int64_t>(dimensions.size())];
}

template <typename ActionsEnum>
ActionsEnum AgentUCB<ActionsEnum>::Action(void)
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
        std::sample(_actions.begin(), _actions.end(), &action, 1, rng);
        // float action{randomAction(rng)};
        
        // for (size_t index{1}; index < _actions.size(); ++index)
        // {
        //     if (action <= float(index) / _actions.size())
        //         action = _actions[index];
        // }
    }
    ++_lastObservationState.actionsStats[action].timesSelected;
    _lastObservationState.lastAction = action;
    ++_episode;

    return action;
}

template <typename ActionsEnum>
void AgentUCB<ActionsEnum>::Observe(const std::vector<float> &observation)
{
    std::vector<int64_t> sampled{SampleInput(observation)};
    if (observation.size() != _inputsAmount)
        throw std::invalid_argument{"Error in [const std::vector<float> &AgentUCB<ActionsEnum>::Observe(const std::vector<float> &observation)]:\n\tobservation does not math size of inputs."};
    
    if (!_states.contains(sampled))
        _states[sampled] = StateActionReward(_actions);

    _lastObservationState = _states[sampled];

    if (_lastObservationState.actionsStats.empty())
        _lastObservationState.actionsStats.reserve(_actions.size());
}

template <typename ActionsEnum>
void AgentUCB<ActionsEnum>::Reward(float reward)
{
    NextReward(_lastObservationState);

    _lastObservationState.totalReward += _lastObservationState.nextReward;
    _lastObservationState.actionsStats[_lastObservationState.lastAction].rewardSum += _lastObservationState.nextReward;
}

template <typename ActionsEnum>
ActionsEnum AgentUCB<ActionsEnum>::UCB(void)
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
    ++_lastObservationState.actionsStats[selectedAction].timesSelected;
    _lastObservationState.lastAction = selectedAction;

    return selectedAction;
}

template <typename ActionsEnum>
float AgentUCB<ActionsEnum>::NextReward(StateActionReward& state)
{
    return state.nextReward = state.nextReward * _rewardRatio;
}

template <typename ActionsEnum>
std::vector<int64_t> AgentUCB<ActionsEnum>::SampleInput(const std::vector<float> &input)
{
    std::vector<int64_t> sampled(input.size());
    std::transform(input.begin(), input.end(), sampled.begin(), [&](float x){return int64_t(x / _sampling);});
    return sampled;
}

template <typename ActionsEnum>
size_t AgentUCB<ActionsEnum>::Sampling(void)
{
    return _sampling;
}

template <typename ActionsEnum>
size_t AgentUCB<ActionsEnum>::SetSampling(size_t sampling)
{
    return _sampling = sampling;
}

template class AgentUCB<IPlayer::PlayerAction>;