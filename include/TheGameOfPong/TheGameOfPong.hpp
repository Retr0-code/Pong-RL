#pragma once
#include <atomic>
#include <memory>
#include <SFML/System.hpp>

#include "IPlayer.hpp"
#include "Scoreboard.hpp"
#include "GameEngine.hpp"
#include "ElasticBall.hpp"

/**
 * @brief Class for the main logic of the game of pong. Does not use SFML rendering API directly, but creates an instance of `GameEngine`
 */
class TheGameOfPong
{
public:
	/**
	 * @brief Construct a new TheGameOfPong object
	 * 
	 * @param player1 shared pointer to first player
	 * @param player2 shared pointer to second player
	 * @param field window's resolution/game field size
	 */
	TheGameOfPong(
		std::shared_ptr<IPlayer> player1,
		std::shared_ptr<IPlayer> player2,
		sf::Vector2u field = {500, 500}
	);

	virtual ~TheGameOfPong();
	
	/**
	 * @brief Starts game thread
	 */
	void Run(void);

	/**
	 * @brief Stops game thread
	 */
	void Stop(void);

	/**
	 * @brief Sets all game-objects to original state
	 */
	void Reset(void);

	/**
	 * @brief Getter for game-field/window's resolution
	 * 
	 * @return const sf::Vector2u& game-field/window's resolution
	 */
	static const sf::Vector2u& Field(void);

	/**
	 * @brief Getter for game-field/window's resolution field rectangle coordinates
	 * 
	 * @return const sf::FloatRect& game-field/window's resolution field rectangle coordinates
	 */
	static const sf::FloatRect& FieldRect(void);

	/**
	 * @brief Set the game's speed multiplier
	 * 
	 * @param factor speed multiplier
	 */
	static void SetSpeedMultiplier(float factor = 1.f);

	/**
	 * @brief Get the game's speed multiplier
	 * 
	 * @return float speed multiplier
	 */
	static float GetSpeedMultiplier(void);

private:
	static float _speedFactor;
	static sf::Vector2u _field;
	static sf::FloatRect _fieldRect;
	std::shared_ptr<IPlayer> _player1;
	std::shared_ptr<IPlayer> _player2;
	std::shared_ptr<ElasticBall> _ball;
	std::shared_ptr<Scoreboard> _scoreboard;
	std::unique_ptr<GameEngine> _engine;
	sf::Thread _engineThread;
};
