#include "TheGameOfPong.hpp"

#define WINDOW_NAME "Pong"

float TheGameOfPong::_speedFactor{1.f};
sf::Vector2u TheGameOfPong::_field{500, 500};
sf::FloatRect TheGameOfPong::_fieldRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(_field));

TheGameOfPong::TheGameOfPong(
    std::shared_ptr<IPlayer> player1,
    std::shared_ptr<IPlayer> player2,
    sf::Vector2u field)
    : _player1(player1), _player2(player2),
    _ball(new ElasticBall(field / uint32_t(2))), _scoreboard(new Scoreboard(field, _player1, _player2)),
    _engine(new GameEngine(GameEngine::SceneObjectsInit{_player1, _player2, _ball, _scoreboard}, field, WINDOW_NAME)),
    _engineThread(&GameEngine::Run, _engine.get())
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
    _engineThread.launch();
}

void TheGameOfPong::Stop(void)
{
    _engine->Stop();
    _engineThread.wait();
}

void TheGameOfPong::Reset(void)
{
    _player1->Reset();
    _player2->Reset();
    _ball->Reset();
    _scoreboard->Reset();
}

const sf::Vector2u& TheGameOfPong::Field(void)
{
    return _field;
}

const sf::FloatRect &TheGameOfPong::FieldRect(void)
{
    return _fieldRect;
}

void TheGameOfPong::SetSpeedMultiplier(float factor)
{
    _speedFactor = factor;
}

float TheGameOfPong::GetSpeedMultiplier(void)
{
    return _speedFactor;
}

TheGameOfPong::~TheGameOfPong()
{
    _engineThread.wait();
}
