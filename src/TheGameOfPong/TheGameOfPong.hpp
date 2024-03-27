#pragma once
#include <memory>
#include <SFML/System.hpp>

#include "Player.hpp"
#include "GameEngine.hpp"
#include "ElasticBall.hpp"

/*	\class	TheGameOfPong
*	\brief	Class for the main logic of the game of pong. Does not use SFML rendering API directly, but creates an instance of GameEngine
*/
class TheGameOfPong
{
public:
	TheGameOfPong(
		const std::shared_ptr<Player>& _player1,
		const std::shared_ptr<Player>& _player2,
		sf::Vector2u field = {500, 500}
	);

	void Run(void);

	void Reset(void);

private:
	sf::Vector2u _field;
	std::shared_ptr<Player> _player1;
	std::shared_ptr<Player> _player2;
	std::shared_ptr<ElasticBall> _ball;
	std::unique_ptr<GameEngine> _engine;
};
