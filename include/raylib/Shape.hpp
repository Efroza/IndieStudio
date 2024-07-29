/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Shape
*/

#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include "raylib.h"

namespace ry {
    namespace v2d {
        class Shape {
            public:
                Shape(const Vector2 position = {0, 0}, const Color color = WHITE);
                ~Shape();
                Vector2 getPosition() const noexcept;
                Color getColor() const noexcept;
                void setPosition(Vector2 position) noexcept;
                void setColor(Color color) noexcept;
                virtual void draw() const noexcept = 0;

            protected:
                Vector2 _position;
                Color _color;

            protected:
            private:
        };
    }
}

#endif /* !SHAPE_HPP_ */