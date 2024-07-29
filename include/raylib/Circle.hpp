/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Circle
*/

#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include "Shape.hpp"
#include <stdlib.h>

namespace ry {
    namespace v2d {
        class Circle : public Shape  {
            public:
                Circle(const size_t radius = 0
                , const Vector2 position = {0, 0}
                , const Color color = WHITE);
                ~Circle();
                size_t getRadius() const noexcept;
                void setRadius(size_t radius) noexcept;
                void draw() const noexcept;

            private:
                size_t _radius;

            protected:
        };
    }
}

#endif /* !CIRCLE_HPP_ */