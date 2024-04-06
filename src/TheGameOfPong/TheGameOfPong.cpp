#include "TheGameOfPong.hpp"

sf::Vector2u TheGameOfPong::_field{500, 500};

TheGameOfPong::TheGameOfPong(
    std::shared_ptr<IPlayer> player1,
    std::shared_ptr<IPlayer> player2,
    sf::Vector2u field)
    : _player1(player1), _player2(player2), _ball(new ElasticBall(field / uint32_t(2))),
    _engine(new GameEngine(GameEngine::SceneObjectsInit{_player1, _player2, _ball}))
{
    _field = field;
}

const sf::Vector2u TheGameOfPong::Field(void)
{
    return _field;
}
