#pragma once
#include <SFML/System.hpp>

class IControlScheme
{
public:
    virtual sf::Keyboard::Key Up(void) const = 0;

    virtual sf::Keyboard::Key Down(void) const = 0;

    virtual ~IControlScheme() = default;
};
