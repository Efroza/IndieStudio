/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Screen
*/

#include <queue>
#include "../include/Screen.hpp"
#include "../include/global.h"

Screen::Screen(Raylib &raylib, Map &map)
: _raylib(&raylib)
, _map(&map)
, _font()
, _position(Vector2{100, 250})
, _size_y(HEIGHT / 11 + HEIGHT / 15 + 30)
, _buttons()
, _is_running(true)
{
    _font = LoadFont("font_gamer");
    _buttons.push_back(std::unique_ptr<Button>(
        new Button({100, 100}, {WIDTH / 12,  70.0f}," add "
        , [&]() {
            if (_chooses.size() < PERSONNAGE_MAX)
                add_chooses();
        })
    ));
    _buttons.push_back(std::unique_ptr<Button>(
        new Button({WIDTH / 1.2, HEIGHT / 1.2}, {300.f,  70.0f}, " valid "
        , [&]() {
            load_info();
            _is_running = false;
        })
    ));
}

Screen::~Screen()
{
}

void Screen::draw_buttons() const noexcept
{
    for (auto &it : _buttons) {
        if (_raylib->getMousePosition().first >= it->getPosition().first && _raylib->getMousePosition().first <= it->getPosition().first + it->getSize().first &&
            _raylib->getMousePosition().second >= it->getPosition().second && _raylib->getMousePosition().second <= it->getPosition().second + it->getSize().second)
                _raylib->drawRectangle({it->getRectangle().x, it->getRectangle().y}, {it->getRectangle().width, it->getRectangle().height}, GREEN);
        else
            _raylib->drawRectangle({it->getRectangle().x, it->getRectangle().y}, {it->getRectangle().width, it->getRectangle().height}, BLACK);
        _raylib->drawText(it->getPosition(), it->getText(), WHITE, _font, 80, 2);
    }
}

void Screen::add_chooses() noexcept
{
    _chooses.emplace_back(new Choose(Vector2{100, _position.y}, *_raylib));
    _position.y += _size_y;
}

void Screen::add_player(Choose &info, float pos_y, float pos_x) noexcept
{
    Character *player;

    _map->setPlayer(pos_y, pos_x, 0);
    player = _map->extractPlayer(pos_y, pos_x);
    if (player == nullptr)
        return;
    if (info.getName().empty())
        player->setName("Player");
    else
        player->setName(info.getName());
    player->setTouchUp(info.getKeyUp());
    player->setTouchDown(info.getKeyDown());
    player->setTouchLeft(info.getKeyLeft());
    player->setTouchRight(info.getKeyRight());
    player->setTouchBomb(info.getKeyBomb());
}

void Screen::add_ia(Choose &info, float pos_y, float pos_x) noexcept
{
    IA *ia;

    _map->setIA(pos_y, pos_x, 0);
    ia = _map->extractIA(pos_y, pos_x);
    if (ia == nullptr)
        return;
    if (info.getName().empty())
        ia->setName("BOT");
    else
        ia->setName(info.getName());
}

void Screen::load_info() noexcept
{
    float x = _map->getMapX();
    float y = _map->getMapY();
    std::queue<Vector2> case_pos;
    Vector2 pos;

    if (x == 0 || y == 0)
        return;
    case_pos.emplace(Vector2{1, 1});
    case_pos.emplace(Vector2{1, y - 2});
    case_pos.emplace(Vector2{x - 2, 1});
    case_pos.emplace(Vector2{x - 2, y - 2});
    for (auto &info : _chooses) {
        if (info->getType() == Choose::Personnage::none)
            continue;
        if (case_pos.empty() == true)
            return;
        pos = case_pos.front();
        if (info->getType() == Choose::Personnage::player)
            add_player(*info, pos.y, pos.x);
        else
            add_ia(*info, pos.y, pos.x);
        case_pos.pop();
    }
}

void Screen::action_buttons()
{
    if (_raylib->isMousePressed())
        for (auto &it : _buttons)
            if (it->isClicked(_raylib->getMousePosition()))
                it->action();
}

void Screen::handles_chooses() noexcept
{
    for (auto &choose : _chooses) {
        choose->action_buttons();
        choose->handle_click();
        choose->handle_writing();
        choose->draw();
    }
}

void Screen::write_text() const noexcept
{
    DrawText("PLAYER: [UP] [DOWN] [LEFT] [RIGHT]", 300, 125, 40, RED);
}

void Screen::run()
{
    Texture2D background = _raylib->LoadImageToTexture("background_control");

    SetExitKey(KEY_ESCAPE);
    ShowCursor();
    while (_raylib->isWindowClosed() == false && _is_running == true)
    {
        _raylib->StartAndEndDrawing(true);
        _raylib->drawTexture({0, 0}, background, WHITE);
        ClearBackground(RAYWHITE);
        write_text();
        draw_buttons();
        action_buttons();
        handles_chooses();
        _raylib->StartAndEndDrawing(false);
    }
    HideCursor();
    if (background.id > 0)
        UnloadTexture(background);
}