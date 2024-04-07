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
    IGameObject::GameObjectPtr paddle{IGameObject::Shape()};
    sf::FloatRect paddleHitbox{paddle->getGlobalBounds()};
    
    if(sf::Keyboard::isKeyPressed(_controls.Up()) && paddleHitbox.top > 0)
        direction = PlayerAction::Up;

    else if(sf::Keyboard::isKeyPressed(_controls.Down())
    && paddleHitbox.top + paddleHitbox.height < TheGameOfPong::Field().y)
        direction = PlayerAction::Down;
    
    paddle->move(0, GetVelocityLimit() * direction * deltaTime.asMicroseconds());
}

template <typename T>
void PlayerHuman<T>::Reset(void)
{
    IGameObject::Reset();
    _score = 0;
    _velocity = 0;
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
