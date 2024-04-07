#pragma once
#include <atomic>
#include <memory>
#include <SFML/System.hpp>

#include "IPlayer.hpp"
#include "GameEngine.hpp"
#include "ElasticBall.hpp"

/*	\class	TheGameOfPong
*	\brief	Class for the main logic of the game of pong. Does not use SFML rendering API directly, but creates an instance of GameEngine
*/
class TheGameOfPong
{
public:
	TheGameOfPong(
		std::shared_ptr<IPlayer> player1,
		std::shared_ptr<IPlayer> player2,
		sf::Vector2u field = {500, 500}
	);

	void Run(void);

	void Stop(void);

	void Reset(void);

	static const sf::Vector2u& Field(void);

	static const sf::FloatRect& FieldRect(void);

	virtual ~TheGameOfPong();

private:
	void RunBackend(void);

private:
	std::atomic_bool _runGame;
	static sf::Vector2u _field;
	static sf::FloatRect _fieldRect;
	std::shared_ptr<IPlayer> _player1;
	std::shared_ptr<IPlayer> _player2;
	std::shared_ptr<ElasticBall> _ball;
	std::unique_ptr<GameEngine> _engine;
	sf::Thread _engineThread;
	sf::Clock _gameClock;
};
