/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** IObjet
*/

#ifndef ICOLLISION_HPP_
#define ICOLLISION_HPP_

#include "raylib.h"
#include "raymath.h"
#include <memory>
#include <iostream>
#include <vector>

class ICollision {
    public:
        virtual ~ICollision() = default;
        virtual const Vector3 &getPosition() noexcept = 0;
        virtual void setPosition(const Vector3 &position) = 0;
        virtual float getRadius() const = 0;
        virtual void setRadius(float) = 0;
        virtual void setType(int) = 0;
        virtual int getType() const = 0;
        virtual bool getActive() const = 0;
        virtual void setActive(bool active) = 0;
        virtual bool isColliding(const ICollision *collision) const noexcept = 0;
        virtual void setCase(size_t y, size_t x) noexcept = 0;
        virtual void setMap(std::vector<std::vector<std::unique_ptr<ICollision>>> &map) = 0;
        virtual std::vector<std::vector<std::unique_ptr<ICollision>>> *getMap() const noexcept = 0;
        virtual ICollision *getBackground() const noexcept = 0;
        virtual void setBackground(ICollision *) noexcept = 0;
        virtual void resetBackground(ICollision *new_background) noexcept = 0;
        virtual bool isDestructible() const noexcept = 0;
        virtual bool die() = 0;
        virtual void draw_background() = 0;
        virtual void action_background() = 0;
        virtual void draw() = 0;
        virtual void action() = 0;

    protected:
    private:
};

#endif /* !ICOLLISION_HPP_ */
