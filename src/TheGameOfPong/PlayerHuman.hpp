#pragma once

#include "IPlayer.hpp"
#include "IControlSheme.hpp"

template <typename T>
class PlayerHuman :
    public IPlayer
{
public:
    PlayerHuman(PlayerSide playerSide, const sf::Vector2f& paddleSize);

    virtual void Update(const sf::Time& deltaTime) override;

    virtual void Reset(void) override;

private:
    constexpr float UpdateVelocity(void)
    {
        return 1 >= std::abs(_currentVelocity) ? _acceleration : 0;
    } 

private:
    const T _controls;
};


class ControlSchemeArrows
    : public IControlScheme
{
public:
    sf::Keyboard::Key Up(void) const override;

    sf::Keyboard::Key Down(void) const override;
};


class ControlSchemeWASD
    : public IControlScheme
{
public:
    sf::Keyboard::Key Up(void) const override;

    sf::Keyboard::Key Down(void) const override;
};
