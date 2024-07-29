/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Wall
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "ACollision.hpp"
#include "raylib/Rectangle.hpp"

class Wall : public ACollision {
    public:
        Wall(bool destructible, const Vector3 &position = {0});
        ~Wall();
        void setPosition(const Vector3 &pos) noexcept override;
        void put_bonus() noexcept;
        void action() override;
        void draw() noexcept;
        bool die() noexcept;

    private:
        ry::v3d::Cube _cube;
};

#endif /* !WALL_HPP_ */
