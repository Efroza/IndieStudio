/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Camera
*/

#include "../../include/raylib/Camera.hpp"
#include <iostream>

ry::v3d::Camera::Camera(
const Vector3 &position
, const Vector3 &target
, const Vector3 &up
, float fovy
, int projection)
: _camera({0})
{
    _camera.position = position;
    _camera.target = target;
    _camera.up = up;
    _camera.fovy = fovy;
    _camera.projection = projection;
}

ry::v3d::Camera::~Camera()
{
}

void ry::v3d::Camera::begin() noexcept
{
    BeginMode3D(_camera);
}

void ry::v3d::Camera::end() noexcept
{
    EndMode3D();
}

const Vector3 &ry::v3d::Camera::getPosition() noexcept
{
    return _camera.position;
}

const Vector3 &ry::v3d::Camera::getTarget() noexcept
{
    return _camera.target;
}

const Vector3 &ry::v3d::Camera::getUp() noexcept
{
    return _camera.up;
}

float ry::v3d::Camera::getFovy() noexcept
{
    return _camera.fovy;
}

int ry::v3d::Camera::getProjection() const noexcept
{
    return _camera.projection;
}

void ry::v3d::Camera::setFovy(float fovy) noexcept
{
    _camera.fovy = fovy;
}

void ry::v3d::Camera::setProjection(int projection) noexcept
{
    _camera.projection = projection;
}

void ry::v3d::Camera::setPosition(const Vector3 &position) noexcept
{
    _camera.position = position;
}

void ry::v3d::Camera::setTarget(const Vector3 &target) noexcept
{
    std::cout << "target x " << target.x << " z: " << target.z << std::endl;
    _camera.target = target;
}

void ry::v3d::Camera::setUp(const Vector3 &up) noexcept
{
    _camera.up = up;
}