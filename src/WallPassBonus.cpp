/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** WallPassBonus
*/

#include "../include/WallPassBonus.hpp"

WallPassBonus::WallPassBonus(Vector3 position) : ACollision(position, true)
{
    _position = position;
    setTexture();
}

WallPassBonus::~WallPassBonus()
{
    UnloadTexture(_texture);
}

void WallPassBonus::applyBonus(Character *bomber) noexcept
{
    bomber->setWallPass(true);
}

void WallPassBonus::draw_background()
{

}

void WallPassBonus::action_background()
{

}

void WallPassBonus::draw()
{
    DrawCubeTexture(_texture, _position, 1, 1, 1, WHITE);
}


void WallPassBonus::action()
{

}

void WallPassBonus::setTexture()
{
    _texture = LoadTexture("assets/wallpassbonus.png");
}