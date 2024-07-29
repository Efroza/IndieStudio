/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** ACollision
*/

#include "../include/ACollision.hpp"
#include "../include/Exception.hpp"
#include "../include/global.h"

ACollision::ACollision(const Vector3 &position, bool destructible, bool active, float radius)
: _position(position)
, _active(active)
, _radius(radius)
, _type(0)
, _destructible(destructible)
, _background(nullptr)
,_case_y(0)
,_case_x(0)
, _map(nullptr)
{
}

ACollision::~ACollision()
{
}

const Vector3 &ACollision::getPosition() noexcept
{
    return _position;
}

void ACollision::setPosition(const Vector3 &position) noexcept
{
    _position = position;
}

float ACollision::getRadius() const noexcept
{
    return _radius;
}

void ACollision::setRadius(float radius) noexcept
{
    _radius = radius;
}

void ACollision::setType(int type) noexcept
{
    _type = type;
}

int ACollision::getType() const noexcept
{
    return _type;
}

bool ACollision::getActive() const noexcept
{
    return _active;
}

void ACollision::setActive(bool active) noexcept
{
    _active = active;
}

bool ACollision::isColliding(const ICollision *collision) const noexcept
{
    return (collision == nullptr) ? false : true;
}

ICollision *ACollision::getBackground() const noexcept
{
    return _background;
}

void ACollision::setBackground(ICollision *background) noexcept
{
    _background = background;
}

void ACollision::action()
{
}

void ACollision::draw()
{
}

std::vector<std::vector<std::unique_ptr<ICollision>>> *ACollision::getMap() const noexcept
{
    return _map;
}

void ACollision::setMap(std::vector<std::vector<std::unique_ptr<ICollision>>> &map)
{
    if (_case_y >= map.size())
        throw Exception("error in case_x from setMap()");
    if (_case_x >= map[_case_y].size())
        throw Exception("error in case_y from setMap()");
    _map = &map;
}

void ACollision::setCase(size_t y, size_t x) noexcept
{
    _case_y = y;
    _case_x = x;
}

bool ACollision::die()
{
    return true;
}

bool ACollision::isDestructible() const noexcept
{
    return _destructible;
}

void ACollision::draw_background()
{
    if (_background == nullptr)
        return;
    _background->draw();
}

void ACollision::action_background()
{
    if (_background == nullptr)
        return;
    if (_background->getActive() == false && _background->die() == true) {
        delete _background;
        _background = nullptr;
        return;
    }
    _background->action();
}

void ACollision::resetBackground(ICollision *new_background) noexcept
{
    if (_background != nullptr)
        delete _background;
    _background = new_background;
}
