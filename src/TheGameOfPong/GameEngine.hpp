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
	
	GameEngine(SceneObjectsInit sceneObjects);

	GameEngine(const SceneObjects& sceneObjects);

	virtual void Render(void);

	virtual ~GameEngine() = default;

private:
	SceneObjects _sceneObjects;
};
