/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Shape
*/

#include "../../include/raylib/Shape.hpp"

ry::v2d::Shape::Shape(const Vector2 position, const Color color)
:_position(position), _color(_color)
{
}

ry::v2d::Shape::~Shape()
{
}

Vector2 ry::v2d::Shape::getPosition() const noexcept
{
    return _position;
}

Color ry::v2d::Shape::getColor() const noexcept
{
    return _color;
}

void ry::v2d::Shape::setPosition(Vector2 position) noexcept
{
    _position = position;
}
void ry::v2d::Shape::setColor(Color color) noexcept
{
    _color = color;
}
