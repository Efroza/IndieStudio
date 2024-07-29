/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Map
*/

#include "../include/Map.hpp"
#include "../include/Wall.hpp"
#include "../include/global.h"
#include "../include/Raylib.hpp"
#include "../include/Character.hpp"
#include "../include/IA.hpp"
#include "../include/raylib/Rectangle.hpp"
#include "../include/Menu.hpp"
#include "../include/Exception.hpp"
#include "../include/Screen.hpp"
#include "chrono"
#include "thread"
    #define KRED "\x1B[31m"
    #define KNRM "\x1B[0m"

Map::Map(int x, int y, Raylib *raylib) : /*_raylib(ray),*/
_mapSizeX(x),
_mapSizeY(y),
_cameraFov(100),
_seen(),
_raylib(raylib)
{
    _win = new Win(_raylib);
    _pause = new Pause(_raylib, std::bind(&Map::loadGame, this, std::placeholders::_1), std::bind(&Map::saveGame, this), std::bind(&Map::draw, this, std::placeholders::_1));
}

void Map::setMapSize(int x, int y)
{
    _mapSizeX = x;
    _mapSizeY = y;
}

void Map::setPlayer(size_t pos_y, size_t pos_x, size_t pos_z)
{
    Character *new_character;
    Vector3 position = {
        (float)pos_x * SIZE_MAP,
        (float)pos_y * SIZE_MAP,
        (float)pos_z * SIZE_MAP};

    if (_map.size() < pos_y)
        return;
    if (_map[pos_y].size() < pos_x)
        return;
    new_character = new Character(
        "assets/player.iqm"
        , getRandomColor()
        , "player"
        , position);
    new_character->setCase(pos_y, pos_x);
    _map[pos_y][pos_x].reset(new_character);
    new_character->setMap(_map);
}

Character *Map::extractPlayer(size_t pos_y, size_t pos_x) noexcept
{
    if (pos_y >= _map.size())
        return nullptr;
    if (pos_x >= _map[pos_y].size())
        return nullptr;
    return dynamic_cast<Character *>(_map[pos_y][pos_x].get());
}

IA *Map::extractIA(size_t pos_y, size_t pos_x) noexcept
{
    if (pos_y >= _map.size())
        return nullptr;
    if (pos_x >= _map[pos_y].size())
        return nullptr;
    return dynamic_cast<IA *>(_map[pos_y][pos_x].get());
}

std::string Map::getRandomColor() noexcept
{
    for (int j = 0; j < _color_skins.size() - 1; j++) {
        if (_color_skins[j].first == false) {
            _color_skins[j].first = true;
            return _color_skins[j].second;
            break;
        }
    }
    return "assets/blue.png";
}

void Map::setIA(size_t pos_y, size_t pos_x, size_t pos_z)
{
    IA *new_character;
    Vector3 position = {
        (float)pos_x * SIZE_MAP,
        (float)pos_y * SIZE_MAP,
        (float)pos_z * SIZE_MAP};

    if (_map.size() < pos_y)
        return;
    if (_map[pos_y].size() < pos_x)
        return;
    new_character = new IA(
        "assets/player.iqm"
        , getRandomColor()
        , "BOT"
        , position
        , 'A');
    new_character->setCase(pos_y, pos_x);
    _map[pos_y][pos_x].reset(new_character);
    new_character->setMap(_map);
}

void Map::setWall(size_t pos_y, size_t pos_x, bool destructible, size_t pos_z)
{
    Wall *wall = nullptr;
    Vector3 position = {
        (float)pos_x * SIZE_MAP,
        (float)pos_y * SIZE_MAP,
        (float)pos_z * SIZE_MAP};

    if (pos_y == 1 && pos_x == 1 || pos_y == 1 && pos_x == _mapSizeX - 2 || pos_y == _mapSizeY - 2 && pos_x == 1 || pos_y == _mapSizeY - 2 && pos_x == _mapSizeX - 2)
        return;
    if (pos_y == 1 && pos_x == 2 || pos_y == 1 && pos_x == _mapSizeX - 3 || pos_y == _mapSizeY - 2 && pos_x == 2 || pos_y == _mapSizeY - 2 && pos_x == _mapSizeX - 3)
        return;
    if (pos_y == 2 && pos_x == 1 || pos_y == 2 && pos_x == _mapSizeX - 2 || pos_y == _mapSizeY - 3 && pos_x == 1 || pos_y == _mapSizeY - 3 && pos_x == _mapSizeX - 2)
        return;
    if (_map.size() < pos_y)
        return;
    if (_map[pos_y].size() < pos_x)
        return;
    wall = new Wall(destructible, position);
    wall->setMap(_map);
    _map[pos_y][pos_x].reset(wall);
}

void Map::setMap()
{
    _map.resize(_mapSizeY);
    for (int i = 0; i < _map.size(); i++)
        _map[i].resize(_mapSizeX);
    for (int i = 1; i < _map.size() - 1; i++) {
        setWall(i, 0, false);
        setWall(i, _map.at(i).size() - 1, false);
        for (int j = 0; j < _map[i].size(); j++) {
            setWall(0, j, false);
            setWall(_map.size() - 1, j, false);
        }
    }
    createPlayers();
}

void Map::createPlayers() noexcept
{
    setPlayer(1, 1, 0);
    setIA(_map.size() - 2, 1, 0);
}

size_t Map::getMapY() const noexcept
{
    return _map.size();
}

size_t Map::getMapX() const noexcept
{
    if (_map.empty() == true)
        return 0;
    return _map.at(0).size();
}

void Map::createObstacle3D()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, _mapSizeX - 1);

    for (int i = 1; i < _map.size(); i++) {
        for (int j = 1; j < _map[0].size(); j++) {
            if (i > 1 && j > 1 && i < _mapSizeY - 2 && j < _mapSizeX - 2  && i % 2 == 0 && j % 2 == 0)
                setWall(i, j, false);
            else if (i == _mapSizeY - 1 || j == _mapSizeX - 1)
                setWall(i, j, false);
            else if (distrib(gen) % 2 != 0 && i % 2 != 0)
                setWall(i, distrib(gen), true);
        }
    }
}

void Map::printMap()
{
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (dynamic_cast<Wall *>(_map[i][j].get()) != nullptr)
                std::cout << "X";
            else if (dynamic_cast<Character *>(_map[i][j].get()) != nullptr)
                std::cout << KRED << "P" << KNRM;
            else if (dynamic_cast<Bomb *>(_map[i][j].get()) != nullptr)
                std::cout << KRED << "O" << KNRM;
            else
                std::cout << ".";
        } std::cout << std::endl;
    }
}

Vector3 Map::getMiddle() const noexcept
{
    size_t mid_y = _map.size() / 2;
    size_t mid_x = _map[mid_y].size() / 2;

    return (Vector3{(float)mid_x * SIZE_MAP, (float)mid_y * SIZE_MAP, 0});
}

void Map::setUpCamera(ry::v3d::Camera &camera) const noexcept
{
    Vector3 position = getMiddle();
    size_t fovy = sqrt(pow(_mapSizeY, 2) + pow(_mapSizeX, 2));

    camera.setTarget(position);
    position.z = DISTANCE_CAMERA;
    camera.setPosition(position);
    camera.setFovy(_cameraFov);
    camera.setUp(Vector3{0, 1, 0});
}

bool Map::character_seen(size_t y, size_t x) noexcept
{
    if (dynamic_cast<Character *>(_map[y][x].get()) == nullptr)
        return false;
    for (auto &adrrs : _seen)
        if (adrrs == _map[y][x].get())
            return true;
    _seen.push_back(_map[y][x].get());
    return false;
}

bool Map::collisionDie(std::unique_ptr<ICollision> &collision) noexcept
{
    if (collision->getActive() == true)
        return false;
    return collision->die();
}

void Map::draw(bool pause)
{
    _seen.clear();
    for (size_t i = 0; i < _map.size(); ++i)
        for (size_t j = 0; j < _map[i].size(); ++j) {
            try {
                if (_map[i][j].get() == nullptr)
                    continue;
                _map[i][j]->setCase(i, j);
                if (_map[i][j]->getMap() == nullptr)
                    _map[i][j]->setMap(_map);
                _map[i][j]->draw_background();
                _map[i][j]->draw();
                if (pause == true)
                    continue;
                if (character_seen(i, j) == false) {
                    _map[i][j]->action_background();
                    _map[i][j]->action();
                }
                if (_map[i][j].get() != nullptr && collisionDie(_map[i][j]) == true) {
                    printMap();
                    _map[i][j].reset(_map[i][j]->getBackground());
                }
            } catch(Exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
}

void Map::loopGame()
{
    bool finish = false;
    bool quit = false;

    setUpCamera(_raylib->getCamera());
    while (!_raylib->isWindowClosed())
    {
        _raylib->updateMusic();
        if (IsKeyPressed(KEY_ESCAPE))
            quit =_pause->screenPause();
        if (quit)
            break;
        _raylib->StartAndEndDrawing(true);
        ClearBackground(RAYWHITE);
        _raylib->drawFPS({10, 10});
        _raylib->cameraControl(true);
        draw();
        std::this_thread::sleep_for(std::chrono::microseconds(3000));

        _raylib->cameraControl(false);
        _raylib->StartAndEndDrawing(false);
        if (getNbOfPlayersRemaining() == 1) {
            finish = true;
            break;
        }
    }
    if (finish)
        _win->screenWin(getColorOfWinner(), getNameOfWinner());
}

void Map::run()
{
    Screen chose_player(*_raylib, *this);

    setMap();
    try {
        if (_raylib == nullptr)
            return;
        if (_need_load)
            if (_pause->beforeGame()) {
                chose_player.run();
                createObstacle3D();
            }
        if (!_need_load) {
            chose_player.run();
            createObstacle3D();
        }
    } catch(Exception &e) {
        std::cout << e.what() << std::endl;
    }
    SetExitKey(KEY_EIGHT);
    printMap();
    loopGame();
}

void Map::setNeedLoad(bool need_load)
{
    _need_load = need_load;
}

void Map::createFileSave()
{
    int number = 1;
    float height = _pause->getHeightLastButton();

    if (_pause->getFirstLastButton().find(".txt") == std::string::npos)
        height = 160.0f;
    if (_save_file == "") {
        while (true) {
            _save_file = "save_" + std::to_string(number) + ".txt";
            if (std::ifstream(_save_file))
                number++;
            else
                break;
        }
    }
    _pause->insertButton(_save_file, {1550.0f, height}, {108.0f, 60.0f}, "Save " + std::to_string(number), [&]() {return;});
}

void Map::saveGame()
{
    std::ofstream file;
    std::vector<std::pair<std::string, std::vector<std::string>>> characters;

    createFileSave();
    file.open(_save_file);
    file.clear();
    characters = getCharacterInMap({ "A", "I", "C", "B"}, &file);
    for (int i = 0; i < characters.size(); i++) {
        file << characters[i].first;
        for (int j = 0; j < characters[i].second.size(); j++)
            file << characters[i].second[j];
        file << std::endl;
    }
    file.close();
}

std::vector<std::pair<std::string, std::vector<std::string>>> Map::getCharacterInMap(std::vector<std::string> _ia, std::ofstream *file) const noexcept
{
    std::vector<std::pair<std::string, std::vector<std::string>>> characters;
    int _ia_number = 0;
    int number = 1;

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (dynamic_cast<Wall *>(_map[i][j].get()) != nullptr) {
                if (_map[i][j]->isDestructible())
                    (*file) << "X";
                else
                    (*file) << "#";
            }   else if (dynamic_cast<IA *>(_map[i][j].get()) != nullptr) {
                (*file) << _ia[_ia_number];
                characters.push_back({_ia[_ia_number], getBonus(dynamic_cast<IA *>(_map[i][j].get()))});
                _ia_number++;
            } else if (dynamic_cast<Character *>(_map[i][j].get()) != nullptr) {
                (*file) << std::to_string(number);
                characters.push_back({std::to_string(number), getBonus(dynamic_cast<Character *>(_map[i][j].get()))});
                number++;
            } else
                (*file) << ".";
        }
        (*file) << std::endl;
    }
    (*file) << "end_map" << std::endl;
    return characters;
}

std::vector<std::string> Map::getBonus(Character *character) const noexcept
{
    std::vector<std::string> bonus;
    std::vector<std::string> tmp;
    std::string str = ";Color=" + character->getColor();

    bonus.push_back(str);
    str.clear();
    setMultipleBonus(character, &bonus);
    setNameAndKey(character, &bonus);
    return bonus;
}

void Map::setMultipleBonus(Character *character, std::vector<std::string> *bonus) const noexcept
{
    std::string str = "";
    size_t current;
    float speed;
    bool wall;
    
    current = character->getFireOfBomb();
    str = ";Fire=" + std::to_string(current);
    bonus->push_back(str);
    str.clear();
    speed = character->getSpeed();
    str = ";Speed=" + std::to_string(speed);
    bonus->push_back(str);
    str.clear();
    current = character->getNbrOfBomb();
    if (current == 0)
        current = 1;
    str = ";NbrOfBomb=" + std::to_string(current);
    bonus->push_back(str);
    str.clear();
    wall = character->getWallPass();
    str = ";WallPass=" + std::to_string(wall);
    bonus->push_back(str);
    str.clear();
}

void Map::setNameAndKey(Character *character, std::vector<std::string> *bonus) const noexcept
{
    std::string str = "";

    str = ";Name=" + character->getName();
    bonus->push_back(str);
    str.clear();
    str = ";Up=" + std::to_string(character->getTouchUp());
    bonus->push_back(str);
    str.clear();
    str = ";Down=" + std::to_string(character->getTouchDown());
    bonus->push_back(str);
    str.clear();
    str = ";Left=" + std::to_string(character->getTouchLeft());
    bonus->push_back(str);
    str.clear();
    str = ";Right=" + std::to_string(character->getTouchRight());
    bonus->push_back(str);
    str.clear();
    str = ";Bomb=" + std::to_string(character->getTouchBomb());
    bonus->push_back(str);
    str.clear();
}

ICollision *Map::handle_char(char character, float y, float x, float z) noexcept
{
    Vector3 position = {x, y, z};

    switch (character)
    {
        case '1':
        case '2':
        case '3':
        case '4':
            return new Character("assets/player.iqm", getRandomColor(), "player", position, character);
        case 'A':
        case 'I':
        case 'C':
        case 'B':
            return new IA("assets/player.iqm", getRandomColor(), "BOT", position, character);
        case '#':
            return new Wall(false, position);
        case 'X':
            return new Wall(true, position);
        case '.':
            return nullptr;
        default:
            return nullptr;
    }
    return nullptr;
}

std::vector<std::string> Map::splitString(std::string &str, std::string delimiter)
{
    std::vector<std::string> result;
    size_t pos = 0;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        result.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}

Character *Map::getCharacterInMap(char character) const noexcept
{
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (dynamic_cast<Character *>(_map[i][j].get()) != nullptr) {
                if (dynamic_cast<Character *>(_map[i][j].get())->getCharacter() == character)
                    return dynamic_cast<Character *>(_map[i][j].get());
            }
        }
    }
    return nullptr;
}

void Map::setElementforCharacter(std::pair<std::string, std::string> pair, Character *character)
{
    std::string element = pair.first;
    std::string to_add = pair.second;
    std::map<std::string, std::function<void()>> map = {
        {"Name", [&]() {character->setName(to_add);}},
        {"Color", [&]() {character->setColor(to_add);}},
        {"Fire", [&]() {character->setFireOfBomb(std::stoi(to_add));}},
        {"Speed", [&]() {character->setSpeed(std::stof(to_add));}},
        {"NbrOfBomb", [&]() {character->setNbrOfBomb(std::stoi(to_add));}},
        {"WallPass", [&]() {character->setWallPass(std::stoi(to_add));}},
        {"Up", [&]() {character->setTouchUp(std::stoi(to_add));}},
        {"Down", [&]() {character->setTouchDown(std::stoi(to_add));}},
        {"Left", [&]() {character->setTouchLeft(std::stoi(to_add));}},
        {"Right", [&]() {character->setTouchRight(std::stoi(to_add));}},
        {"Bomb", [&]() {character->setTouchBomb(std::stoi(to_add));}}
    };
    map[element]();
}

void Map::setEachElement(std::vector<std::string> elements, Character *character)
{
    elements.erase(elements.begin());
    std::pair<std::string, std::string> pair;
    
    for (int i = 0; i < elements.size(); i++) {
        auto index = elements[i].find('=');
        pair.first = elements[i].substr(0, index);
        pair.second = elements[i].substr(index + 1);
        setElementforCharacter(pair, character);
    }
}

void Map::setCharacterInMap(std::vector<std::string> characters)
{
    std::vector<std::string> tmp;

    for (int i = 0; i < characters.size(); i++) {
        tmp = splitString(characters[i], ";");
        setEachElement(tmp, getCharacterInMap(tmp[0][0]));
    }
}

void Map::loadGame(const std::string &file)
{
    std::fstream file_;
    size_t counter = 0;
    std::string line;
    std::vector<std::string> characters;
    bool end_map = false;
    size_t number = 0;

    file_.open(file);
    if (!file_.is_open())
        throw Exception("File " + file + " cannot be opened.");
    _map.clear();
    for (; file_.good(); counter++) {
        std::getline(file_, line);
        if (line.empty())
            break;
        if (!end_map)
            _map.resize(counter + 1);
        if (end_map) {
            characters.push_back(line);
        }
        if (line.find("end_map") != std::string::npos) {
            end_map = true;
            number = counter;
        }
        if (!end_map) {
            _map.resize(line.size());
            for (size_t x = 0; x <= line.size() - 1; ++x)
                _map[counter].emplace_back(std::unique_ptr<ICollision>(handle_char(line[x], counter, x, 0)));
            _mapSizeX = line.size();
        }
        line.clear();
    }
    _mapSizeY = number;
    _map.resize(_mapSizeY);
    file_.close();
    setCharacterInMap(characters);
    return;
}

int Map::getNbOfPlayersRemaining() const noexcept
{
    int nb = 0;

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (dynamic_cast<Character *>(_map[i][j].get()) != nullptr)
                nb++;
        }
    }
    return nb;
}

std::string Map::getColorOfWinner() const noexcept
{
    std::string color = "";

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (dynamic_cast<Character *>(_map[i][j].get()) != nullptr)
                color = dynamic_cast<Character *>(_map[i][j].get())->getColor();
        }
    }
    return color;
}

std::string Map::getNameOfWinner() const noexcept
{
    std::string name = "";

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++)
            if (dynamic_cast<Character *>(_map[i][j].get()) != nullptr)
                name = dynamic_cast<Character *>(_map[i][j].get())->getName();
    }
    return name;
}
