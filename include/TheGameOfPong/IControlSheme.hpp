#pragma once
#include <SFML/System.hpp>

/**
 * @brief Interface class for player's control scheme
 */
class IControlScheme
{
public:
    /**
     * @brief Pure virtual function for Up action
     * 
     * @return sf::Keyboard::Key key related to `IPlayer::PlayerAction::Up`
     */
    virtual sf::Keyboard::Key Up(void) const = 0;

    /**
     * @brief Pure virtual function for Down action
     * 
     * @return sf::Keyboard::Key key related to `IPlayer::PlayerAction::Down`
     */
    virtual sf::Keyboard::Key Down(void) const = 0;

    virtual ~IControlScheme() = default;
};
