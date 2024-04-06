#pragma once
#include <vector>
#include <initializer_list>

#include "IGameObject.hpp"

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

	virtual ~GameEngine();

private:
	SceneObjects _sceneObjects;
	std::unique_ptr<sf::RenderWindow> _window;
};
