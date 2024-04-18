#include "TheGameOfPong.hpp"

#define WINDOW_NAME "Pong"
#define DELTA_TIME  1.f / 256.f

sf::Vector2u TheGameOfPong::_field{500, 500};
sf::FloatRect TheGameOfPong::_fieldRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(_field));

TheGameOfPong::TheGameOfPong(
    std::shared_ptr<IPlayer> player1,
    std::shared_ptr<IPlayer> player2,
    sf::Vector2u field)
    : _runGame(false), _player1(player1), _player2(player2),
    _ball(new ElasticBall(field / uint32_t(2))), _scoreboard(new Scoreboard(field, _player1, _player2)),
    _engine(new GameEngine(GameEngine::SceneObjectsInit{_player1, _player2, _ball, _scoreboard}, field, WINDOW_NAME)),
    _engineThread(&TheGameOfPong::RunBackend, this)
{
    _field = field;
    _ball->SetPlayers(_player1, _player2);
    _player1->SetBall(_ball);
    _player1->SetOtherPlayer(_player2);
    _player2->SetBall(_ball);
    _player2->SetOtherPlayer(_player1);
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
    _gameClock.restart();
    while (_runGame)
    {
        sf::Time deltaTime{_gameClock.getElapsedTime()};

        if (deltaTime.asSeconds() > DELTA_TIME)
        {
            _gameClock.restart();
            _player1->Update(deltaTime);
            _player2->Update(deltaTime);
            _ball->Update(deltaTime);
            _scoreboard->Update(deltaTime);
        }
        _engine->Render();
    }
}
