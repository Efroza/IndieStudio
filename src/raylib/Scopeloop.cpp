/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** Scopeloop
*/

#include "../../include/raylib/Scopeloop.hpp"

ry::Scopeloop::Scopeloop(const Color color)
{
    BeginDrawing();
    ClearBackground(color);
}

ry::Scopeloop::~Scopeloop()
{
    EndDrawing();
}