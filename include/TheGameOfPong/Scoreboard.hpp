#pragma once

#include "IGameObject.hpp"

class IPlayer;

/**
 * @brief Scoreboard class describes game object displaying players' scores
 */
class Scoreboard
    : public IGameObject
{
public:
    /**
     * @brief alias for std::shared_ptr<IPlayer>
     */
    using IPlayerShared = std::shared_ptr<IPlayer>;

    /**
     * @brief Construct a new Scoreboard object
     * 
     * @param field game-field/windows resolution
     * @param leftPlayer player on left
     * @param rightPlayer player on right
     */
    Scoreboard(const sf::Vector2u& field, IPlayerShared leftPlayer, IPlayerShared rightPlayer);

    /**
     * @brief Total reset to 0:0
     */
    virtual void Reset(void) override;

    /**
     * @brief `GameEngine` update function
     * 
     * @param deltaTime time between frames
     */
    virtual void Update(const sf::Time& deltaTime) override;

private:
    static IDrawable* CreateText(const sf::Vector2u& field);

    std::string FormatValues(void);

private:
    IPlayerShared _leftPlayer;
    IPlayerShared _rightPlayer;
};