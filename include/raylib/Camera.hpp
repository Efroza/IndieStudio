/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "raylib.h"

namespace ry {
    namespace v3d {
        class Camera {
            public:
                Camera(const Vector3 &position = {0.0f}
                , const Vector3 &target = {0.0f}
                , const Vector3 &up = {0.0f}
                , float fovy = 0.0f
                , int projection = CAMERA_PERSPECTIVE);
                ~Camera();
                void begin() noexcept;
                void end() noexcept;
                const Vector3 &getPosition() noexcept;
                const Vector3 &getTarget() noexcept;
                const Vector3 &getUp() noexcept;
                float getFovy() noexcept;
                int getProjection() const noexcept;
                void setFovy(float fovy) noexcept;
                void setProjection(int projection) noexcept;
                void setPosition(const Vector3 &position) noexcept;
                void setTarget(const Vector3 &target) noexcept;
                void setUp(const Vector3 &up) noexcept;

            private:
                Camera3D _camera;
        };
    }
}

#endif /* !CAMERA_HPP_ */