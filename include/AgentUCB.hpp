#pragma once
#include <vector>
#include <unordered_map>

#include "IAgent.hpp"

template <typename ActionsEnum>
class AgentUCB
    : public IAgent<float, ActionsEnum>
{
public:
    using ActionsSpace = std::vector<ActionsEnum>;
    using StateDimensions = std::vector<std::pair<float, float>>;

    typedef struct
    {
        size_t timesSelected;
        float rewardSum;
        float upperBound;
    } ActionsStats;

    typedef struct
    {
        float totalReward;
        float nextReward;
        std::unordered_map<ActionsEnum, ActionsStats> actionsStats;
    } StateActionReward;

    AgentUCB(const StateDimensions& dimensions, const ActionsSpace& actions, float epsilon = 0.f, float rewardRatio = 1.f);

    virtual ActionsEnum& Action(void) override;

    virtual const std::vector<float>& Observe(const std::vector<float>& observation) override;

    virtual void Reward(bool positive = true) override;

private:
    ActionsEnum& UCB(void);

    float NextReward(StateActionReward& state);

private:
    size_t _episode;
    size_t _inputsAmount;
    float _epsilon;
    float _rewardRatio;
    float _totalReward;
    ActionsSpace _actions;
    StateActionReward& _lastObservationState;
    std::unordered_map<std::vector<float>, StateActionReward> _states;
};
