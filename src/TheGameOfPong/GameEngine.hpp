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
	using SceneObjects = std::vector<const IGameObject*>;
	
	GameEngine(std::initializer_list<const IGameObject*> sceneObjects);

	GameEngine(const SceneObjects& sceneObjects);

	void Render(void);

private:
	SceneObjects _sceneObjects;
};
