/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** main
*/

#include <filesystem>
#include <string>
#include <chrono>
#include <cstdlib>
#include <vector>
#include "../include/Menu.hpp"
#include "../include/Map.hpp"
#include "raylib.h"
#include "raymath.h"
#include "../include/Bomb.hpp"
#include "../include/Character.hpp"
#include "../include/FireUpBonus.hpp"
#include "../include/BombBonus.hpp"
#include "../include/SpeedBonus.hpp"
#include "../include/WallPassBonus.hpp"
#include "../include/IBonus.hpp"
#include "../include/raylib/Camera.hpp"
#include "../include/raylib/Rectangle.hpp"
#include "../include/raylib/Scopeloop.hpp"

int main(void)
{
    Raylib raylib(WIDTH, HEIGHT, "Bomberman");
    Menu menu(&raylib);

    raylib.setMusic("bomberman_sound");
    menu.AnimationBeforeMenu();
    return 0;
}