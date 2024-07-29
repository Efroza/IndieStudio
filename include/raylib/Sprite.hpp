/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "raylib.h"
#include <iostream>

namespace ry {
    namespace v2d {
        class Sprite {
            public:
                Sprite(const Vector2 pos = {0, 0}, const Color color = WHITE);
                Sprite(const std::string &file_texture, const Vector2 pos = {0, 0}, const Color _color = WHITE);
                void setTexture(const std::string &file_texture) noexcept;
                void setColor(const Color color) noexcept;
                void setTime(const float time) noexcept;
                void setPosition(const Vector2 position) noexcept;
                void autoRect(const size_t div_x, const size_t div_y) noexcept;
                void moveRect() noexcept;
                void move(const int x, const int y) noexcept;
                void draw() const noexcept;
                ~Sprite();

            private:
                Vector2 _pos;
                Color _color;
                Texture2D _texture;
                float _time;
                int _width;
                int _height;
                Vector2 _react;
                Vector2 _actual;

            protected:
        };
    }
}

#endif /* !SPRITE_HPP_ */