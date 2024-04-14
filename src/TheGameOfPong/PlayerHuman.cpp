#include <iostream>
#include <type_traits>
#include "TheGameOfPong.hpp"
#include "PlayerHuman.hpp"

template <typename T>
PlayerHuman<T>::PlayerHuman(PlayerSide playerSide, const sf::Vector2f &paddleSize)
    : IPlayer(playerSide, paddleSize)
{
    static_assert(std::is_base_of<IControlScheme, T>::value,
        "Error: PlayerHuman<T>::PlayerHuman T must be a derived class of IControlScheme."
    );
}

template <typename T>
void PlayerHuman<T>::Update(const sf::Time& deltaTime)
{
    PlayerAction direction{PlayerAction::Stay};
    sf::FloatRect paddleHitbox{IGameObject::_shape->getGlobalBounds()};

    if(sf::Keyboard::isKeyPressed(_controls.Up())
    && TheGameOfPong::FieldRect().contains({IGameObject::_shape->getPosition().x, paddleHitbox.top}))
    {
        direction = PlayerAction::Up;
        _currentVelocity -= UpdateVelocity();
    }

    else if(sf::Keyboard::isKeyPressed(_controls.Down())
    && TheGameOfPong::FieldRect().contains({IGameObject::_shape->getPosition().x, paddleHitbox.top + paddleHitbox.height}))
    {
        direction = PlayerAction::Down;
        _currentVelocity += UpdateVelocity();
    }
    else
        _currentVelocity *= _acceleration;

    IGameObject::_shape->move(0, _velocityLimit * direction * deltaTime.asSeconds());
}

template <typename T>
void PlayerHuman<T>::Reset(void)
{
    IPlayer::Reset();
    _score = 0;
}

inline sf::Keyboard::Key ControlSchemeArrows::Up(void) const
{
    return sf::Keyboard::Key::Up;
}

inline sf::Keyboard::Key ControlSchemeArrows::Down(void) const
{
    return sf::Keyboard::Key::Down;
}

inline sf::Keyboard::Key ControlSchemeWASD::Up(void) const
{
    return sf::Keyboard::Key::W;
}

inline sf::Keyboard::Key ControlSchemeWASD::Down(void) const
{
    return sf::Keyboard::Key::S;
}

template class PlayerHuman<ControlSchemeArrows>;
template class PlayerHuman<ControlSchemeWASD>;
