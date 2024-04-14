#pragma once
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/*	\class	IGameObject
*	\brief	Interface class for all objects in game scene
*/
class IGameObject
{
public:
	using GameObjectPtr = std::shared_ptr<sf::RectangleShape>;

	IGameObject(const sf::Vector2f& position, sf::RectangleShape* shape);

	virtual const sf::RectangleShape* Shape(void) const;

	virtual GameObjectPtr Shape(void);

	virtual void Reset(void);
	
	virtual void Update(const sf::Time& deltaTime) = 0;

	virtual ~IGameObject() = default;

protected:
	GameObjectPtr _shape;
	sf::RectangleShape _originalShape;
};
