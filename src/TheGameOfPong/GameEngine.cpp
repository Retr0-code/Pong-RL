#include "GameEngine.hpp"

#define WINDOW_FRAME_LIMIT 300

GameEngine::GameEngine(
    SceneObjectsInit sceneObjects,
    const sf::Vector2u& resolution,
    const sf::String& windowTitle
    )
    : _runGame(false), _window(new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), windowTitle))
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
    : _runGame(false), _sceneObjects(sceneObjects),
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

void GameEngine::Run(void)
{
    _runGame = true;
    _gameClock.restart();
    while (_runGame)
    {
        sf::Time deltaTime{_gameClock.getElapsedTime()};

        if (deltaTime.asSeconds() > DELTA_TIME)
        {
            _gameClock.restart();
            for (auto obj : _sceneObjects)
                obj->Update(deltaTime);
        }
        Render();
    }
}

void GameEngine::Stop(void)
{
    _runGame = false;
}

GameEngine::~GameEngine()
{
    _runGame = false;
    _window->close();
}
