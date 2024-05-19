#pragma once

#include "IPlayer.hpp"
#include "IControlSheme.hpp"

/**
 * @brief Class defines player controlled by human
 * 
 * @tparam ControlScheme class derived from `IControlScheme`
 */
template <typename ControlScheme>
class PlayerHuman :
    public IPlayer
{
public:
    /**
     * @brief Construct a new Player Human object
     * 
     * @param playerSide assigns players side
     * @param paddleSize assigns static paddleSize
     */
    PlayerHuman(PlayerSide playerSide, const sf::Vector2f& paddleSize);

    /**
     * @brief `GameEngine` update function
     * 
     * @param deltaTime time between frames
     */
    virtual void Update(const sf::Time& deltaTime) override;

    /**
     * @brief Total player reset
     */
    virtual void Reset(void) override;

    /**
     * @brief Score update based on reward
     * 
     * @param reward 
     */
    virtual void UpdateScore(Reward reward) override;

private:
    const ControlScheme _controls;
};


/**
 * @brief ControlScheme class for arrows keys
 */
class ControlSchemeArrows
    : public IControlScheme
{
public:
    /**
     * @brief Function for Up action
     * 
     * @return sf::Keyboard::Key::Up;
     */
    sf::Keyboard::Key Up(void) const override;

    /**
     * @brief Function for Down action
     * 
     * @return sf::Keyboard::Key::Down;
     */
    sf::Keyboard::Key Down(void) const override;
};


/**
 * @brief ControlScheme class for W/S keys
 */
class ControlSchemeWASD
    : public IControlScheme
{
public:
    /**
     * @brief Function for Up action
     * 
     * @return sf::Keyboard::Key::W;
     */
    sf::Keyboard::Key Up(void) const override;

    /**
     * @brief Function for Down action
     * 
     * @return sf::Keyboard::Key::S;
     */
    sf::Keyboard::Key Down(void) const override;
};
