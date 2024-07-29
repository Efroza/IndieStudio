/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** BombBonus
*/

#include "../include/BombBonus.hpp"

BombBonus::BombBonus(Vector3 position) : ACollision(position, true)
{
    _position = position;
    setTexture();
}

BombBonus::~BombBonus()
{
    if (_texture.id > 0)
        UnloadTexture(_texture);
}

void BombBonus::applyBonus(Character *bomber) noexcept
{
    bomber->setNbrOfBomb(bomber->getNbrOfBomb() + 1);
}

void BombBonus::draw_background()
{

}

void BombBonus::action_background()
{

}

void BombBonus::draw()
{
    DrawCubeTexture(_texture, _position, 1, 1, 1, WHITE);
}


void BombBonus::action()
{

}

void BombBonus::setTexture()
{
    _texture = LoadTexture("assets/bombbonus.png");
}