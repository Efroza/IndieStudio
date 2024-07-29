/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <memory>
#include <filesystem>
#include <cstdlib>
#include "Info.hpp"
#include "ICollision.hpp"
#include "raylib/Camera.hpp"
#include "IA.hpp"
#include "Button.hpp"
#include "Raylib.hpp"
#include <fstream>
#include "Win.hpp"
#include "Pause.hpp"

struct State
{
    bool isAlive;
    bool isWidget;
    bool isBomb;
    bool isWall;
    bool isAi;
};

class Screen;

class Map {
    public:
        Map(int width, int height, Raylib *raylib = nullptr);
        ~Map() = default;
        void setMap();
        void setMapSize(int, int);
        size_t getMapY() const noexcept;
        size_t getMapX() const noexcept;
        void setPlayer(size_t pos_y, size_t pos_x, size_t pos_z);
        void setIA(size_t pos_y, size_t pos_x, size_t pos_z);
        Character *extractPlayer(size_t pos_y, size_t pos_x) noexcept;
        IA *extractIA(size_t pos_y, size_t pos_x) noexcept;
        void setWall(size_t pos_y, size_t pos_x, bool destructible = true, size_t pos_z = 0);
        void setUpCamera(ry::v3d::Camera &camera) const noexcept;
        void createObstacle3D();
        void createPlayers() noexcept;
        Vector3 getMiddle() const noexcept;
        void printMap();
        void run();
        void loopGame();
        void draw(bool pause = false);
        std::string remove_useless(std::string str);
        void saveGame();
        void loadGame(const std::string &file);
        std::string getRandomColor() noexcept;
        int getNbOfPlayersRemaining() const noexcept;
        std::string getColorOfWinner() const noexcept;
        std::string getNameOfWinner() const noexcept;
        void screenWin(std::string);
        std::vector<std::string> getBonus(Character *player) const noexcept;
        void setMultipleBonus(Character *, std::vector<std::string> *) const noexcept;
        void setNameAndKey(Character *, std::vector<std::string> *) const noexcept;
        void beforeGame();
        void setNeedLoad(bool);
        void createFileSave();
        std::vector<std::pair<std::string, std::vector<std::string>>> getCharacterInMap(std::vector<std::string> _ia, std::ofstream *file) const noexcept;
        void setCharacterInMap(std::vector<std::string>);
        std::vector<std::string> splitString(std::string &str, std::string delimiter);
        Character *getCharacterInMap(char character) const noexcept;
        void setEachElement(std::vector<std::string>, Character *);
        void setElementforCharacter(std::pair<std::string, std::string>, Character *);

    private:
        bool character_seen(size_t y, size_t x) noexcept;
        bool collisionDie(std::unique_ptr<ICollision> &collision) noexcept;
        ICollision *handle_char(char character, float y, float x, float z) noexcept;

    private:
        int _mapSizeX;
        int _mapSizeY;
        float _cameraFov;
        std::vector<ICollision *> _seen;
        std::vector<std::vector<std::unique_ptr<ICollision>>> _map;
        Raylib *_raylib;
        std::string _save_file = "";
        bool _load_save = false;
        std::vector<std::pair<bool, std::string>> _color_skins {
            {false, "assets/red.png"},
            {false, "assets/green.png"},
            {false, "assets/blue.png"},
            {false, "assets/purple.png"},
            {false, "assets/yellow.png"},
            {false, "assets/cyan.png"},
        };
        Win *_win;
        Pause *_pause;
        bool _need_load = true;
};

#endif /* !MAP_HPP_ */