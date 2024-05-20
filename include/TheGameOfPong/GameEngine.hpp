#pragma once
#include <vector>
#include <atomic>
#include <initializer_list>

#include "IGameObject.hpp"

/**
 * @brief physics tickrate
 */
#define DELTA_TIME  (1.f / 256.f)

/**
 * @brief Updates all IGameObjects on screen using SFML frontend
 */
class GameEngine
{
public:
	/**
	 * @brief alias to std::vector<std::shared_ptr<`IGameObject`>>
	 */
	using SceneObjects = std::vector<std::shared_ptr<IGameObject>>;
	/**
	 * @brief alias to std::initializer_list<std::shared_ptr<`IGameObject`>>
	 */
	using SceneObjectsInit = std::initializer_list<std::shared_ptr<IGameObject>>;
	
	/**
	 * @brief Construct a new GameEngine object
	 * 
	 * @param sceneObjects vector of game objects
	 * @param resolution window resolution
	 * @param windowTitle windows title
	 */
	GameEngine(
		SceneObjectsInit sceneObjects,
		const sf::Vector2u& resolution,
		const sf::String& windowTitle
		);

	/**
	 * @brief Construct a new GameEngine object
	 * 
	 * @param sceneObjects vector of game objects
	 * @param resolution window resolution
	 * @param windowTitle windows title
	 */
	GameEngine(
		const SceneObjects& sceneObjects,
		const sf::Vector2u& resolution,
		const sf::String& windowTitle
		);

	/**
	 * @brief Renders every scene object
	 */
	virtual void Render(void);

	/**
	 * @brief Main engine update loop
	 */
	virtual void Run(void);

	/**
	 * @brief Stops engine update loop
	 */
	virtual void Stop(void);

	virtual ~GameEngine();

private:
	std::atomic_bool _runGame;
	sf::Clock _gameClock;
	SceneObjects _sceneObjects;
	std::unique_ptr<sf::RenderWindow> _window;
};
