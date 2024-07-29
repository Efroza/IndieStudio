/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Circle
*/

#include "../../include/raylib/Circle.hpp"

ry::v2d::Circle::Circle(const size_t radius, const Vector2 position, const Color color)
: Shape(position, color), _radius(radius)
{
}

ry::v2d::Circle::~Circle()
{
}

size_t ry::v2d::Circle::getRadius() const noexcept
{
    return _radius;
}

void ry::v2d::Circle::setRadius(size_t radius) noexcept
{
    _radius = radius;
}

void ry::v2d::Circle::draw() const noexcept
{
    DrawCircleV(_position, _radius, _color);
}