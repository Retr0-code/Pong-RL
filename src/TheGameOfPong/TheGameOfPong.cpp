#include "TheGameOfPong.hpp"

#define WINDOW_NAME "Pong"

sf::Vector2u TheGameOfPong::_field{500, 500};
sf::FloatRect TheGameOfPong::_fieldRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(_field));

TheGameOfPong::TheGameOfPong(
    std::shared_ptr<IPlayer> player1,
    std::shared_ptr<IPlayer> player2,
    sf::Vector2u field)
    : _runGame(false), _player1(player1), _player2(player2), _ball(new ElasticBall(field / uint32_t(2))),
    _engine(new GameEngine(GameEngine::SceneObjectsInit{_player1, _player2, _ball}, field, WINDOW_NAME)),
    _engineThread(&TheGameOfPong::RunBackend, this)
{
    _field = field;
}

void TheGameOfPong::Run(void)
{
    _runGame = true;
    _engineThread.launch();
}

void TheGameOfPong::Stop(void)
{
    _runGame = false;
    _engineThread.wait();
}

const sf::Vector2u& TheGameOfPong::Field(void)
{
    return _field;
}

const sf::FloatRect &TheGameOfPong::FieldRect(void)
{
    return _fieldRect;
}

TheGameOfPong::~TheGameOfPong()
{
    _engineThread.wait();
}

void TheGameOfPong::RunBackend(void)
{
    while (_runGame)
    {
        _gameClock.restart();
        sf::Time deltaTime{_gameClock.getElapsedTime()};
        _player1->Update(deltaTime);
        _player2->Update(deltaTime);
        _ball->Update(deltaTime);
        _engine->Render();
    }
}
