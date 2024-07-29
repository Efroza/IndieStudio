/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Sprite
*/

#include "../../include/raylib/Sprite.hpp"
#include "../../include/Exception.hpp"
#include <chrono>
#include <thread>

ry::v2d::Sprite::Sprite(const Vector2 pos, const Color color)
: _pos(pos),
_color(color),
_texture(),
_time(0),
_width(0),
_height(0),
_react({0}),
_actual({0})
{
}

ry::v2d::Sprite::Sprite(const std::string &file_texture, const Vector2 pos, const Color color)
    : _pos(pos), _color(color)
{
    setTexture(file_texture);
}

ry::v2d::Sprite::~Sprite()
{
}

void ry::v2d::Sprite::setTexture(const std::string &file_texture) noexcept
{
    Image image;

    image = LoadImage(file_texture.c_str());

    try {
        if (image.data = NULL)
            throw Exception("error in loading file: " + file_texture);
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    _texture = LoadTextureFromImage(image);
    _width = image.width;
    _height = image.height;
    if (image.data != NULL)
        UnloadImage(image);
}

void ry::v2d::Sprite::setTime(const float time) noexcept
{
    _time = time;
}

void ry::v2d::Sprite::move(int x, int y) noexcept
{
    _pos.x += x;
    _pos.y += y;
}


void ry::v2d::Sprite::autoRect(const size_t div_x, const size_t div_y) noexcept
{
    if (_height == 0 || _width == 0)
        return;
    _react.x = _width / div_x;
    _react.y = _height / div_x;
}

void ry::v2d::Sprite::moveRect() noexcept
{
    if (_react.y == 0 || _react.x == 0)
        return;
    if (_actual.x + _react.x < _width) {
        _actual.x + _react.x;
        return;
    }
    _actual.x = 0;
    if (_actual.y + _react.y < _height) {
        _actual.y + _react.y;
        return;
    }
    _actual.y = 0;
}

void ry::v2d::Sprite::draw() const noexcept
{
    if (_react.y == 0 || _react.x == 0) {
        DrawTexture(_texture, _pos.x, _pos.y, _color);
        return;
    }
    DrawTextureRec(_texture
    , Rectangle{_actual.x, _actual.y, _react.x, _react.y}
    , _pos, _color);
    std::this_thread::sleep_for(std::chrono::microseconds((int)(_time * 10) + 1));
}

void ry::v2d::Sprite::setColor(const Color color) noexcept
{
    _color = color;
}

void ry::v2d::Sprite::setPosition(const Vector2 position) noexcept
{
    _pos = position;
}