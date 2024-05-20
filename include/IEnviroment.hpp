#pragma once
#include <vector>

/**
 * @brief Interface class for RL environment
 * 
 * @tparam ActionsEnum enumeration of available actions in environment (have to be same as an agent has)
 * @tparam T type for observation
 */
template <typename ActionsEnum, typename T>
class IEnvironment
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
     * @brief Function returns std::set of actions
     * 
     * @return const ActionsSpace& availabe actions in the environment
     */
    const ActionsSpace& ActionSpace(void) const
    {
        return _actionSpace;
    }

    /**
     * @brief Functions returns description of states space as a vector of pairs of start and end values
     * 
     * @return const StateDimensions& states space descriptor
     */
    virtual const StateDimensions& States(void) const
    {
        return _states;
    }

protected:
    StateDimensions _states;    // Field to filled in sub class
    ActionsSpace _actionSpace;  // Field to filled in sub class
};
