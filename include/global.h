/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** global
*/

#ifndef GLOBAL_H_
#define GLOBAL_H_

    #define SIZE_MAP 1
    #define DISTANCE_CAMERA 10
    #define PROFONDEUR 0.5
    #define PERSONNAGE_MAX 4
    #define NAME_MAX 30

    #define LEFT_SIDE(map, x, y) (x == 0) ? map[y][x] : map[y][x - 1]
    #define RIGHT_SIDE(map, x, y) (x == (map[y].size() - 1)) ? map[y][x] : map[y][x + 1]
    #define DOWN_SIDE(map, x, y) (y == 0) ? map[y][x] : map[y - 1][x]
    #define UP_SIDE(map, x, y) (y == (map.size() - 1)) ? map[y][x] : map[y + 1][x]

#endif /* !GLOBAL_H_ */
