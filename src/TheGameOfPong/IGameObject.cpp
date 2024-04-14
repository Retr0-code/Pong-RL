#include "IGameObject.hpp"

using GameObjectPtr = std::shared_ptr<IDrawable>;

IGameObject::IGameObject(const sf::Vector2f& position, IDrawable* shape)
	: _shape(shape)
{
	_shape->SetPosition(position);
	_originalShape = std::unique_ptr<IDrawable>(_shape->Clone());
}

const IDrawable *IGameObject::Shape(void) const
{
    return _shape.get();
}

GameObjectPtr IGameObject::Shape(void)
{
    return _shape;
}

void IGameObject::Reset(void)
{
	_shape->Copy(*_originalShape);
}
