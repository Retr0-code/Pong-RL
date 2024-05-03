#pragma once
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "IDrawable.hpp"

/*	\class	IGameObject
*	\brief	Interface class for all objects in game scene
*/
class IGameObject
{
public:
	using GameObjectPtr = std::shared_ptr<IDrawable>;

	IGameObject(const sf::Vector2f& position, IDrawable* shape);

	virtual const IDrawable* Shape(void) const;

	virtual GameObjectPtr Shape(void);

	virtual void Reset(void);
	
	virtual void Update(const sf::Time& deltaTime) = 0;

	virtual ~IGameObject() = default;

protected:
	GameObjectPtr _shape;
	std::unique_ptr<IDrawable> _originalShape;
};
