#pragma once
#include <set>
#include <vector>
#include <atomic>
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
        
        hash ^= (hash >> 20) ^ (hash >> 12);
        return hash ^ (hash >> 7) ^ (hash >> 4);
    }
};

template <typename ActionsEnum>
class AgentUCB
    : public IAgent<float, ActionsEnum>
{
public:
    using ActionsSpace = std::set<ActionsEnum>;
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

        StateActionReward(const ActionsSpace& actionsSpace) : totalReward(0.f), nextReward(0.f)
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

    virtual float GetReward(void) const override;

    static size_t Sampling(void);

    static size_t SetSampling(size_t sampling);

    virtual void SetEpsilon(float epsilon);

    virtual size_t NextEpisode(void) override;
    
    virtual size_t Episode(void) const override;

    virtual void Reset(void) override;

private:
    ActionsEnum UCB(void);

    std::vector<int64_t> SampleInput(const std::vector<float>& input);

    size_t StatesTotalSize(const StateDimensions& dimensions);

private:
    static size_t _sampling;

    std::atomic_size_t _episode;
    size_t _inputsAmount;
    const size_t _statesAmount;
    float _epsilon;
    float _rewardRatio;
    const float _rewardRatioOriginal;
    std::atomic<float> _totalReward;
    const ActionsSpace _actions;
    static StateActionReward _emptyObservationState;
    StateActionReward* _lastObservationState;
    std::unordered_map<std::vector<int64_t>, StateActionReward, Int64VectorHash> _states;
};
