/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Wall
*/

#include <memory>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <functional>
#include "../include/Wall.hpp"
#include "../include/global.h"
#include "../include/FireUpBonus.hpp"
#include "../include/BombBonus.hpp"
#include "../include/SpeedBonus.hpp"
#include "../include/WallPassBonus.hpp"

static const std::vector<std::function<IBonus *(Vector3)>> all_bonus = {
    [](Vector3 position)
    { return new FireUpBonus(position); },
    [](Vector3 position)
    { return new BombBonus(position); },
    [](Vector3 position)
    { return new SpeedBonus(position); },
    [](Vector3 position)
    { return new FireUpBonus(position); },
    [](Vector3 position)
    { return new WallPassBonus(position); },
};

Wall::Wall(bool destructible, const Vector3 &position) : ACollision(position, destructible),
                                                            _cube(Vector3{SIZE_MAP, SIZE_MAP, PROFONDEUR}, position, RED)
{
    if (destructible == false)
        _cube.setColor(RED);
    else
        _cube.setColor(BROWN);
}

Wall::~Wall()
{
}

void Wall::setPosition(const Vector3 &pos) noexcept
{
    _position = pos;
    _cube.setPosition(_position);
}

void Wall::action()
{
}

void Wall::draw() noexcept
{
    _cube.draw(BLACK);
}

void Wall::put_bonus() noexcept
{

    ICollision *bonus_wall;

    if (_map == nullptr || (*_map)[_case_y][_case_x].get() == nullptr)
        return;
    std::srand(std::time(NULL));
    if ((std::rand() % 4) + 1 == 1) {
        int generation = (std::rand() % 4) + 1;
        bonus_wall = dynamic_cast<ICollision *>(all_bonus[generation](_position));
        if (bonus_wall == nullptr)
            return;
        setBackground(bonus_wall);
        std::cout << generation << std::endl;
    } else
            std::cout << "No Bonus" << std::endl;
}

bool Wall::die() noexcept
{
    put_bonus();
    return true;
}
