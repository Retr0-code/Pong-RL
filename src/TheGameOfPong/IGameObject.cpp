#include "IGameObject.hpp"

using GameObjectPtr = std::shared_ptr<sf::RectangleShape>;

IGameObject::IGameObject(const sf::Vector2f& position, sf::RectangleShape* shape)
	: _shape(shape), _originalShape(*shape)
{
	_shape->setPosition(position);
	_originalShape.setPosition(position);
}

const sf::RectangleShape *IGameObject::Shape(void) const
{
    return _shape.get();
}

GameObjectPtr IGameObject::Shape(void)
{
    return _shape;
}

void IGameObject::Reset(void)
{
	*_shape = _originalShape;
}
