#pragma once
#include "IPlayer.hpp"
#include "IEnviroment.hpp"
#include "TheGameOfPong.hpp"

/**
 * @brief Class that describes environment as 5 parameters ball position (x, y), player position (y), ball velocity vector (x, y)
 */
class EnvironmentPong5I
    : public IEnvironment<IPlayer::PlayerAction, int64_t>
{
public:
    /**
     * @brief alias for td::set<IPlayer::PlayerAction>
     */
    using ActionsSpace = std::set<IPlayer::PlayerAction>;
    /**
     * @brief alias for std::vector<std::pair<int64_t, int64_t>>
     */
    using StateDimensions = std::vector<std::pair<int64_t, int64_t>>;

    /**
     * @brief Construct a new Environment Pong that initializes 5 parameters state dimension and player's action set
     */
    EnvironmentPong5I(void);
};

class EnvironmentPong3I
    : public IEnvironment<IPlayer::PlayerAction, int64_t>
{
public:
    /**
     * @brief alias for td::set<IPlayer::PlayerAction>
     */
    using ActionsSpace = std::set<IPlayer::PlayerAction>;
    /**
     * @brief alias for std::vector<std::pair<int64_t, int64_t>>
     */
    using StateDimensions = std::vector<std::pair<int64_t, int64_t>>;

    /**
     * @brief Construct a new Environment Pong that initializes 3 parameters state dimension and player's action set
     */
    EnvironmentPong3I(void);
};