#pragma once
#include <SFML/Graphics.hpp>

class IDrawable
{
public:
    IDrawable& operator=(const IDrawable&) = delete;

    virtual sf::Drawable& Get(void) = 0;

    virtual void SetPosition(sf::Vector2f coordinates) = 0;

    virtual IDrawable* Clone(void) const = 0;

    virtual IDrawable& Copy(const IDrawable&) = 0;
};

class DrawableRect
    : public IDrawable
{
public:
    DrawableRect(sf::Vector2f size) : _shape(size) {  }

    virtual IDrawable& Copy(const DrawableRect& otherShape)
    {
        _shape = otherShape._shape;
        return *this;
    }

    virtual IDrawable& Copy(const IDrawable& shape) override
    {
        return Copy(static_cast<const DrawableRect&>(shape));
    }

    virtual sf::Drawable& Get(void)
    {
        return _shape;
    }

    virtual void SetPosition(sf::Vector2f coordinates)
    {
        _shape.setPosition(coordinates);
    }

    virtual IDrawable* Clone(void) const override
    {
        return new DrawableRect(*this);
    }

private:
    sf::RectangleShape _shape;
};

class DrawableText
    : public IDrawable
{
    DrawableText(float fontSize)
    {
        _text.setCharacterSize(fontSize);
    }

    virtual IDrawable& Copy(const DrawableText& otherShape)
    {
        _text = otherShape._text;
        return *this;
    }

    virtual IDrawable& Copy(const IDrawable& shape) override
    {
        return Copy(static_cast<const DrawableRect&>(shape));
    }

    virtual sf::Drawable& Get(void)
    {
        return _text;
    }

    virtual void SetPosition(sf::Vector2f coordinates)
    {
        _text.setPosition(coordinates);
    }

    virtual IDrawable* Clone(void) const override
    {
        return new DrawableText(*this);
    }

private:
    sf::Text _text;
};