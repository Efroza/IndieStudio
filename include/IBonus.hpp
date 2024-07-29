/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** IBonus
*/

#ifndef IBONUS_HPP_
#define IBONUS_HPP_

#include "raylib.h"
#include "raymath.h"
#include <memory>
#include <iostream>
#include <vector>
#include "Character.hpp"

class IBonus {
    public:
        virtual ~IBonus() = default;
        virtual void applyBonus(Character *) noexcept = 0;
        virtual void draw_background() = 0;
        virtual void action_background() = 0;
        virtual void draw() = 0;
        virtual void action() = 0;
        virtual void setTexture() = 0;
    protected:
    private:
};

#endif /* !IBONUS_HPP_ */
