/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** FireUpBonus
*/

#include "../include/FireUpBonus.hpp"

FireUpBonus::FireUpBonus(Vector3 position) : ACollision(position, true)
{
    _position = position;
    setTexture();
}

FireUpBonus::~FireUpBonus()
{
    if (_texture.id > 0)
        UnloadTexture(_texture);
}

void FireUpBonus::applyBonus(Character *bomber) noexcept
{
    bomber->setFireOfBomb(bomber->getFireOfBomb() + 1);
}

void FireUpBonus::draw_background()
{

}

void FireUpBonus::action_background()
{

}

void FireUpBonus::draw()
{
    DrawCubeTexture(_texture, _position, 1, 1, 1, WHITE);
}


void FireUpBonus::action()
{

}

void FireUpBonus::setTexture()
{
    _texture = LoadTexture("assets/fireupbonus.png");
}