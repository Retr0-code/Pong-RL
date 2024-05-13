#include <cmath>
#include <limits>
#include <random>
#include <iostream>
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
    _actions(actions), _rewardRatio(rewardRatio), _totalReward(0.f),
    _episode(0), _lastObservationState(&_emptyObservationState)
{
    size_t totalSize{1};
    for (auto& borders : dimensions)
        totalSize *= (std::abs(borders.first) + std::abs(borders.second)) / _sampling;

    _states.reserve(totalSize);
    _lastObservationState = &_states[std::vector<int64_t>(dimensions.size())];
}

template <typename ActionsEnum>
ActionsEnum AgentUCB<ActionsEnum>::Action(void)
{
    if (_epsilon == 0.0)
    {
        ++_episode;
        return UCB();
    }

    // Inititialize with last action in vector
    ActionsEnum action{*(_actions.end() - 1)};

    std::random_device randomDevice;
    std::default_random_engine rng(randomDevice());
    std::uniform_real_distribution<float> actionChoice(0.f, 1.f);
    
    float prob{actionChoice(rng)};
    if (_epsilon >= prob)
    {
        std::sample(_actions.begin(), _actions.end(), &action, 1, rng);
        ++_lastObservationState->actionsStats[action].timesSelected;
        _lastObservationState->lastAction = action;
    }
    else 
        action = UCB();

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

    _lastObservationState = &_states[sampled];
}

template <typename ActionsEnum>
void AgentUCB<ActionsEnum>::Reward(float reward)
{
    if (reward == 0)
        return ;
    
    _totalReward += reward * _rewardRatio;
    _lastObservationState->totalReward += reward * _rewardRatio;
    // ActionsStats* action{&_lastObservationState->actionsStats[_lastObservationState->lastAction]};
    // action->rewardSum += reward * _rewardRatio;
    _lastObservationState->actionsStats[_lastObservationState->lastAction].rewardSum += reward * _rewardRatio;
    _rewardRatio *= _rewardRatio;

    std::cout << _totalReward << '\n';
}

template <typename ActionsEnum>
size_t AgentUCB<ActionsEnum>::Episode(void) const
{
    return _episode;
}

template <typename ActionsEnum>
ActionsEnum AgentUCB<ActionsEnum>::UCB(void)
{
    ActionsEnum selectedAction{_actions[0]};
    float maxUpperBound{0};
    for (auto& [action, actionStats] : _lastObservationState->actionsStats)
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
    ++_lastObservationState->actionsStats[selectedAction].timesSelected;
    _lastObservationState->lastAction = selectedAction;

    return selectedAction;
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

template <typename ActionsEnum>
void AgentUCB<ActionsEnum>::SetEpsilon(float epsilon)
{
    if (epsilon >= 0)
        _epsilon = epsilon;
}

template <typename ActionsEnum>
size_t AgentUCB<ActionsEnum>::NextEpisode(void)
{
    return ++_episode;
}

template class AgentUCB<IPlayer::PlayerAction>;