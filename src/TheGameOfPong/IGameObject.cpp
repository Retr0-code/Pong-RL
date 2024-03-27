#include "IGameObject.hpp"

using GameObjectPtr = std::shared_ptr<sf::Shape>;

IGameObject::IGameObject(const sf::Vector2f& position, sf::Shape* shape)
	: _shape(shape), _initialOrigin(shape->getOrigin()), _initialPosition(position)
{
	_shape->setPosition(position);
}

const sf::Shape* IGameObject::Shape(void) const
{
	return _shape.get();
}

GameObjectPtr& IGameObject::Shape(void)
{
	return _shape;
}

void IGameObject::Reset(void)
{
	_shape->setOrigin(_initialOrigin);
	_shape->setPosition(_initialPosition);
}
