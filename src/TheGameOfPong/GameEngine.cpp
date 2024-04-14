#include "GameEngine.hpp"

#define WINDOW_FRAME_LIMIT 300

GameEngine::GameEngine(
    SceneObjectsInit sceneObjects,
    const sf::Vector2u& resolution,
    const sf::String& windowTitle
    )
    : _window(new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), windowTitle))
{
    for (auto i : sceneObjects)
    {
        if (i == nullptr)
            throw std::invalid_argument{"Error: GameEngine::GameEngine nullptr was in initializer list."};
        
        _sceneObjects.push_back(i);
    }
    _window->setFramerateLimit(WINDOW_FRAME_LIMIT);
}

GameEngine::GameEngine(
		const SceneObjects& sceneObjects,
		const sf::Vector2u& resolution,
		const sf::String& windowTitle
		)
    : _sceneObjects(sceneObjects),
    _window(new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), windowTitle))
{
    for (auto i : _sceneObjects)
        if (i == nullptr)
            throw std::invalid_argument{"Error: GameEngine::GameEngine nullptr was in SceneObjects."};
}

void GameEngine::Render(void)
{
    _window->clear(sf::Color::Black);

    for (auto obj : _sceneObjects)
        _window->draw(obj->Shape()->Get());

    _window->display();
}

GameEngine::~GameEngine()
{
    _window->close();
}
