#pragma once
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "IDrawable.hpp"

/**
 * @brief Interface class for all objects in game scene
 */
class IGameObject
{
public:
	/**
	 * @brief alias to std::shared_ptr<IDrawable>
	 */
	using GameObjectPtr = std::shared_ptr<IDrawable>;

	/**
	 * @brief Construct a new IGameObject object
	 * 
	 * @param position 2D float coordinates vector
	 * @param shape pointer that will be taken over
	 */
	IGameObject(const sf::Vector2f& position, IDrawable* shape);

	/**
	 * @brief Constant getter for `IGameObject::_shape`
	 * 
	 * @return const IDrawable* `IGameObject::_shape`
	 */
	virtual const IDrawable* Shape(void) const;

	/**
	 * @brief Getter for `IGameObject::_shape`
	 * 
	 * @return IDrawable* `IGameObject::_shape`
	 */
	virtual GameObjectPtr Shape(void);

	/**
	 * @brief Sets object to default `IGameObject::_originalShape`
	 */
	virtual void Reset(void);
	
	/**
	 * @brief Interface update function for `GameEngine`
	 * 
	 * @param deltaTime time between frames
	 */
	virtual void Update(const sf::Time& deltaTime) = 0;

	virtual ~IGameObject() = default;

protected:
	GameObjectPtr _shape;
	std::unique_ptr<IDrawable> _originalShape;
};
