/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** SpeedBonus
*/

#include "../include/SpeedBonus.hpp"

SpeedBonus::SpeedBonus(Vector3 position) : ACollision(position, true)
{
    _position = position;
    setTexture();
}

SpeedBonus::~SpeedBonus()
{
    if (_texture.id > 0)
        UnloadTexture(_texture);
}

void SpeedBonus::applyBonus(Character *bomber) noexcept
{
    bomber->setSpeed(0.2f);
}

void SpeedBonus::draw_background()
{

}

void SpeedBonus::action_background()
{

}

void SpeedBonus::draw()
{
    DrawCubeTexture(_texture, _position, 1, 1, 1, WHITE);
}

void SpeedBonus::action()
{

}

void SpeedBonus::setTexture()
{
    _texture = LoadTexture("assets/speedbonus.png");
}