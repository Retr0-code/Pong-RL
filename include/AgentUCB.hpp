#pragma once
#include <set>
#include <vector>
#include <atomic>
#include <unordered_map>

#include "IAgent.hpp"

/**
 * @brief Class that contains hashing algorithm for std::vector<int64_t> 
 */
class Int64VectorHash
{
public:
    /**
     * @brief Hashing operator for std::vector<int64_t>
     * 
     * @param input vector of any size
     * @return size_t hash of given vector
     */
    size_t operator()(const std::vector<int64_t>& input) const
    {
        size_t hash{1};
        for (float x : input)
            hash = 31 * hash + x;
        
        hash ^= (hash >> 20) ^ (hash >> 12);
        return hash ^ (hash >> 7) ^ (hash >> 4);
    }
};

/**
 * @brief Class for Upper-Confidence bound RL agent
 * 
 * @tparam ActionsEnum enumeration of available actions
 */
template <typename ActionsEnum>
class AgentUCB
    : public IAgent<float, ActionsEnum>
{
public:
    /**
     * @brief alias for td::set<ActionsEnum>
     */
    using ActionsSpace = std::set<ActionsEnum>;
    /**
     * @brief alias for std::vector<std::pair<int64_t, int64_t>>
     */
    using StateDimensions = std::vector<std::pair<int64_t, int64_t>>;

    /**
     * @brief Structure for actions statistics (times selected, reward sum and its UCB)
     */
    struct ActionsStats
    {
        size_t timesSelected;
        float rewardSum;
        float upperBound;

        ActionsStats(void) : timesSelected(0), rewardSum(0.f), upperBound(0.f) {  }
    };

    /**
     * @brief Cell in states' space contains data about all actions available in the state
     */
    struct StateActionReward
    {
        float totalReward;
        ActionsEnum lastAction;
        std::unordered_map<ActionsEnum, ActionsStats, std::hash<int>> actionsStats;

        StateActionReward(void) : totalReward(0.f) {  }

        StateActionReward(const ActionsSpace& actionsSpace) : totalReward(0.f)
        {
            ActionsStats empty;
            for (auto& action : actionsSpace)
                actionsStats.emplace(action, empty);
        }
    };

    /**
     * @brief Construct a new AgentUCB object
     * 
     * @param dimensions states space as a vector of pairs of start and end values
     * @param actions set of available actions
     * @param epsilon ratio for espilon-greedy strategy (exploration rate)
     * @param rewardRatio discount rate
     */
    AgentUCB(const StateDimensions& dimensions, const ActionsSpace& actions, float epsilon = 0.f, float rewardRatio = 1.f);

    /**
     * @brief Overloaded interface function of taking action
     * 
     * @return ActionsEnum 
     */
    virtual ActionsEnum Action(void) override;

    /**
     * @brief Overloaded interface function for creating an observation
     * 
     * @param observation 
     */
    virtual void Observe(const std::vector<float>& observation) override;

    /**
     * @brief Overloaded interface function for updating agent's reward
     * 
     * @param reward value of reward (default = 1)
     */
    virtual void Reward(float reward = 1.f) override;

    /**
     * @brief Getter for total reward
     * 
     * @return float total agent's reward
     */
    virtual float GetReward(void) const override;

    /**
     * @brief Function gives sampling ratio value
     * 
     * @return size_t sampling ratio
     */
    static size_t Sampling(void);

    /**
     * @brief Set the sampling to a new value
     * 
     * @param sampling new sampling
     * @return size_t new sampling ration
     */
    static size_t SetSampling(size_t sampling);

    /**
     * @brief Set the Epsilon ratio
     * 
     * @param epsilon new eps ratio
     */
    virtual void SetEpsilon(float epsilon);

    /**
     * @brief Overloaded interface function for switching agent to a new episode
     * 
     * @return size_t new episode
     */
    virtual size_t NextEpisode(void) override;
    
    /**
     * @brief Getter for total episodes passed
     * 
     * @return size_t total episodes passed
     */
    virtual size_t Episode(void) const override;

    /**
     * @brief Reset function for agent
     */
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
