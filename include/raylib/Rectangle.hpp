/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include "Shape.hpp"

namespace ry {
    namespace v2d {
        class Rectangle : public ry::v2d::Shape {
            public:
                Rectangle(const Vector2 size = {0, 0}
                , const Vector2 position = {0, 0}
                , const Color color = WHITE);
                ~Rectangle();
                Vector2 getSize() const noexcept;
                void setSize(Vector2 size) noexcept;
                void draw(Color around) const noexcept;
                void draw() const noexcept;
                bool checkCollision(Vector2 pos) noexcept;

            private:
                Vector2 _size;
            protected:
        };
    }
    namespace v3d {
        class Cube {
            public:
                Cube (const Vector3 size = {0 ,0 , 0},
                const Vector3 position = {0 ,0 , 0}
                , const Color color = WHITE);
                ~Cube();
                Vector3 getPosition() const noexcept;
                Color getColor() const noexcept;
                void move(const Vector3 move) noexcept;
                void setPosition(const Vector3 position) noexcept;
                void setSize(const Vector3 size) noexcept;
                void setColor(const Color color) noexcept;
                void draw(const Color color = MAROON) const noexcept;

            private:
                Vector3 _size;
                Vector3 _position;
                Color _color;
        };
    }
}

#endif /* !RECTANGLE_HPP_ */