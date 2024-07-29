/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** ry::v2d::Rectangle
*/

#include "../../include/raylib/Rectangle.hpp"

ry::v2d::Rectangle::Rectangle(const Vector2 size, const Vector2 position, const Color color)
: Shape(position, color), _size(size)
{
}

ry::v2d::Rectangle::~Rectangle()
{
}

Vector2 ry::v2d::Rectangle::getSize() const noexcept
{
    return _size;
}

void ry::v2d::Rectangle::setSize(Vector2 size) noexcept
{
    _size = size;
}

void ry::v2d::Rectangle::draw(Color around) const noexcept
{
    DrawRectangleV(_position, _size, _color);
    DrawRectangleLines(_position.x - 1, _position.y - 1, _size.x + 1, _size.y + 1, around);
}

void ry::v2d::Rectangle::draw() const noexcept
{
    DrawRectangleV(_position, _size, _color);
}

ry::v3d::Cube::Cube(const Vector3 size, const Vector3 position, const Color color)
: _size(size), _position(position), _color(color)
{
}

ry::v3d::Cube::~Cube()
{
}

Vector3 ry::v3d::Cube::getPosition() const noexcept
{
    return _position;
}

Color ry::v3d::Cube::getColor() const noexcept
{
    return _color;
}

void ry::v3d::Cube::move(const Vector3 move) noexcept
{
    _position.x = _position.x + move.x;
    _position.y = _position.y + move.y;
    _position.z = _position.z + move.z;
}
void ry::v3d::Cube::setPosition(const Vector3 position) noexcept
{
    _position = position;
}

void ry::v3d::Cube::setSize(const Vector3 size) noexcept
{
    _size = size;
}

void ry::v3d::Cube::setColor(const Color color) noexcept
{
    _color = color;
}

void ry::v3d::Cube::draw(const Color color) const noexcept
{
    DrawCubeV(_position, _size, _color);
    DrawCubeWiresV(_position, _size, color);
}