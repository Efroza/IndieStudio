/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Info
*/

#include "../include/Info.hpp"

void Info::setBlock(bool block)
{
    _block = block;
}

void Info::setBomb(bool bomb)
{
    _bomb = bomb;
}

bool Info::isBlock() const
{
    return _block;
}

bool Info::isBomb() const
{
    return _bomb;
}

bool Info::isSol() const noexcept
{
    return !_block && !_bomb;
}