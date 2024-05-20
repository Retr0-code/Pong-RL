#pragma once
#include <set>
#include <vector>
#include <cstdint>


/**
 * @brief Interface class for RL agents
 * 
 * @tparam T type for calculations
 * @tparam ActionsEnum enumeration of agent actions
 */
template <typename T, typename ActionsEnum>
class IAgent
{
public:
    /**
     * @brief alias for td::set<ActionsEnum>
     */
    using ActionsSpace = std::set<ActionsEnum>;
    /**
     * @brief alias for std::vector<std::pair<T, T>>
     */
    using StateDimensions = std::vector<std::pair<T, T>>;

    /**
     * @brief Pure virtual function for taking an action
     * 
     * @return ActionsEnum chosen action
     */
    virtual ActionsEnum Action(void) = 0;

    /**
     * @brief Pure virtual function for observing environment state
     * 
     * @param observation vector of input values
     */
    virtual void Observe(const std::vector<T>& observation) = 0;

    /**
     * @brief Pure virtual function for rewarding an agent
     * 
     * @param reward value of reward (default 1.0)
     */
    virtual void Reward(float reward = 1.f) = 0;
    
    /**
     * @brief Getter for total reward
     * 
     * @return T total reward
     */
    virtual T GetReward(void) const = 0;

    /**
     * @brief Pure virtual getter function of episodes amount
     * 
     * @return size_t total episodes passed
     */
    virtual size_t Episode(void) const = 0;
    
    /**
     * @brief Pure virtual function for changing episode
     * 
     * @return size_t updated episodes amount
     */
    virtual size_t NextEpisode(void) = 0;

    /**
     * @brief Pure virtual function for resetting an agent to an original state
     */
    virtual void Reset(void) = 0;

    virtual ~IAgent() = default;
};
