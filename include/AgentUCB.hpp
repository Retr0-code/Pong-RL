#pragma once
#include <vector>
#include <unordered_map>

#include "IAgent.hpp"

class Int64VectorHash
{
public:
    size_t operator()(const std::vector<int64_t>& input) const
    {
        size_t hash{1};
        for (float x : input)
            hash = 31 * hash + x;
            // hash = 31 * hash + *reinterpret_cast<int*>(&x);
        
        hash ^= (hash >> 20) ^ (hash >> 12);
        return hash ^ (hash >> 7) ^ (hash >> 4);
    }
};

template <typename ActionsEnum>
class AgentUCB
    : public IAgent<float, ActionsEnum>
{
public:
    using ActionsSpace = std::vector<ActionsEnum>;
    using StateDimensions = std::vector<std::pair<int64_t, int64_t>>;

    struct ActionsStats
    {
        size_t timesSelected;
        float rewardSum;
        float upperBound;

        ActionsStats(void) : timesSelected(0), rewardSum(0.f), upperBound(0.f) {  }
    };

    struct StateActionReward
    {
        float totalReward;
        float nextReward;
        ActionsEnum lastAction;
        std::unordered_map<ActionsEnum, ActionsStats, std::hash<int>> actionsStats;

        StateActionReward(void) : totalReward(0.f), nextReward(0.f) {  }

        StateActionReward(const std::vector<ActionsEnum>& actionsSpace) : totalReward(0.f), nextReward(0.f)
        {
            ActionsStats empty;
            for (auto& action : actionsSpace)
                actionsStats.emplace(action, empty);
        }
    };

    AgentUCB(const StateDimensions& dimensions, const ActionsSpace& actions, float epsilon = 0.f, float rewardRatio = 1.f);

    virtual ActionsEnum Action(void) override;

    virtual void Observe(const std::vector<float>& observation) override;

    virtual void Reward(float reward = 1.f) override;

    static size_t Sampling(void);

    static size_t SetSampling(size_t sampling);

private:
    ActionsEnum UCB(void);

    float NextReward(StateActionReward& state);

    std::vector<int64_t> SampleInput(const std::vector<float>& input);

private:
    static size_t _sampling;
    size_t _episode;
    size_t _inputsAmount;
    float _epsilon;
    float _rewardRatio;
    float _totalReward;
    ActionsSpace _actions;
    static StateActionReward _emptyObservationState;
    StateActionReward& _lastObservationState;
    std::unordered_map<std::vector<int64_t>, StateActionReward, Int64VectorHash> _states;
};
