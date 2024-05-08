#pragma once
#include <vector>
#include <atomic>
#include <initializer_list>

#include "IGameObject.hpp"

#define DELTA_TIME  1.f / 256.f

/*	\class	GameEngine
*	\brief	Updates all IGameObjects on screen using SFML frontend
*/
class GameEngine
{
public:
	using SceneObjects = std::vector<std::shared_ptr<IGameObject>>;
	using SceneObjectsInit = std::initializer_list<std::shared_ptr<IGameObject>>;
	
	GameEngine(
		SceneObjectsInit sceneObjects,
		const sf::Vector2u& resolution,
		const sf::String& windowTitle
		);

	GameEngine(
		const SceneObjects& sceneObjects,
		const sf::Vector2u& resolution,
		const sf::String& windowTitle
		);

	virtual void Render(void);

	virtual void Run(void);

	virtual void Stop(void);

	virtual ~GameEngine();

private:
	std::atomic_bool _runGame;
	sf::Clock _gameClock;
	SceneObjects _sceneObjects;
	std::unique_ptr<sf::RenderWindow> _window;
};
