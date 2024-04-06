#include "GameEngine.hpp"

GameEngine::GameEngine(SceneObjectsInit sceneObjects)
{
    for (auto i : sceneObjects)
    {
        if (i == nullptr)
            throw std::invalid_argument{"Error: GameEngine::GameEngine nullptr was in initializer list."};
        
        _sceneObjects.push_back(i);
    }
}

GameEngine::GameEngine(const SceneObjects &sceneObjects)
    : _sceneObjects(sceneObjects)
{
    for (auto i : _sceneObjects)
        if (i == nullptr)
            throw std::invalid_argument{"Error: GameEngine::GameEngine nullptr was in SceneObjects."};
}

void GameEngine::Render(void)
{
}

