#pragma once

#include <SFML/System.hpp>

/*	\class	IGameObject
*	\brief	Interface class for all objects in game scene
*/
class IGameObject
{
public:
	sf::Vector2f Origin() const;

	sf::Vector2f& Origin();

	sf::Vector2f Coordinates() const;

	sf::Vector2f& Coordinates();

	sf::Vector2f Shape() const;

	sf::Vector2f& Shape();

	virtual ~IGameObject() = default;

protected:
	sf::Vector2f _origin;
	sf::Vector2f _coordinates;
	sf::Vector2f _shape;
};
