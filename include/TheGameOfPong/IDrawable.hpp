#pragma once
#include <SFML/Graphics.hpp>

#include "FontCourier.hpp"

/**
 * @brief Interface class for drawable SFML objects
 */
class IDrawable
{
public:
    IDrawable& operator=(const IDrawable&) = delete;

    /**
     * @brief Pure virtual Get function returns reference to sf::Drawable object
     * 
     * @return sf::Drawable& SFML drawable object
     */
    virtual sf::Drawable& Get(void) = 0;

    /**
     * @brief Pure virtual function setting the position of SFML drawable object
     * 
     * @param coordinates 2D vector of coordinates
     */
    virtual void SetPosition(sf::Vector2f coordinates) = 0;

    /**
     * @brief Pure virtual function creates new SFML drawable object on heap
     * 
     * @return IDrawable* new SFML drawable object
     */
    virtual IDrawable* Clone(void) const = 0;

    /**
     * @brief Pure virtual function copies a given object
     * 
     * @param other object to create a copy of
     * 
     * @return IDrawable& this object
     */
    virtual IDrawable& Copy(const IDrawable& other) = 0;
};

/**
 * @brief Rectangle shape wrapper for SFML sf::RectangleShape
 */
class DrawableRect
    : public IDrawable
{
public:
    /**
     * @brief Construct a new DrawableRect object
     * 
     * @param size 2D float vector rectangle size
     */
    DrawableRect(sf::Vector2f size) : _shape(size) {  }

    /**
     * @brief Copies other DrawableRect
     * 
     * @param otherShape reference to copieble object
     * @return IDrawable& this object
     */
    virtual IDrawable& Copy(const DrawableRect& otherShape)
    {
        _shape = otherShape._shape;
        return *this;
    }

    /**
     * @brief Interface function for copieng
     * 
     * @param shape reference to copieble object
     * @return IDrawable& this object
     */
    virtual IDrawable& Copy(const IDrawable& shape) override
    {
        return Copy(static_cast<const DrawableRect&>(shape));
    }

    /**
     * @brief Getter of `DrawableRect::_shape`
     * 
     * @return sf::Drawable& SFML sf::RectangleShape upcasted object
     */
    virtual sf::Drawable& Get(void)
    {
        return _shape;
    }

    /**
     * @brief Set the position of sf::RectangleShape object
     * 
     * @param coordinates 2D float vector of coordinates
     */
    virtual void SetPosition(sf::Vector2f coordinates)
    {
        _shape.setPosition(coordinates);
    }

    /**
     * @brief Create new DrawableRect object on a heap
     * 
     * @return IDrawable* newly created object
     */
    virtual IDrawable* Clone(void) const override
    {
        return new DrawableRect(*this);
    }

private:
    sf::RectangleShape _shape;
};

/**
 * @brief sf::Text wrapper with `IDrawable` interface
 */
class DrawableText
    : public IDrawable
{
public:
    /**
     * @brief Construct a new DrawableText object
     * 
     * @param fontSize size of font
     */
    DrawableText(uint32_t fontSize)
    {
        _font.loadFromMemory(_font_courier_ttf, _font_courier_ttf_size);
        _text.setFont(_font);
        _text.setFillColor(sf::Color::White);
        _text.setCharacterSize(fontSize);
        _text.setString("0 : 0");
        _text.setOrigin(_text.getLocalBounds().width / 2.f, 0);
    }

    /**
     * @brief Copies other DrawableText
     * 
     * @param otherShape reference to copieble object
     * @return IDrawable& this object
     */
    virtual IDrawable& Copy(const DrawableText& otherShape)
    {
        _text = otherShape._text;
        return *this;
    }

    /**
     * @brief Interface function for copieng
     * 
     * @param shape reference to copieble object
     * @return IDrawable& this object
     */
    virtual IDrawable& Copy(const IDrawable& shape) override
    {
        return Copy(static_cast<const DrawableRect&>(shape));
    }

    /**
     * @brief Getter of `DrawableText::_text`
     * 
     * @return sf::Drawable& SFML sf::Text upcasted object
     */
    virtual sf::Drawable& Get(void)
    {
        return _text;
    }

    /**
     * @brief Set the position of sf::Text object
     * 
     * @param coordinates 2D float vector of coordinates
     */
    virtual void SetPosition(sf::Vector2f coordinates)
    {
        _text.setPosition(coordinates);
    }

    /**
     * @brief Create new DrawableText object on a heap
     * 
     * @return IDrawable* newly created object
     */
    virtual IDrawable* Clone(void) const override
    {
        return new DrawableText(*this);
    }

private:
    sf::Font _font;
    sf::Text _text;
};
