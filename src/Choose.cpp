/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Choose
*/

#include "../include/Choose.hpp"
#include "../include/global.h"

Choose::Choose(Vector2 position, Raylib &raylib)
:
_position(position)
, _raylib(&raylib)
,_nameBox(Vector2{WIDTH / 3, HEIGHT / 11}, position, BLACK)
, _upBox(Vector2{WIDTH / 15, HEIGHT / 15}, Vector2{position.x, position.y + HEIGHT / 10}, BLACK)
, _downBox(Vector2{WIDTH / 15, HEIGHT / 15}, Vector2{position.x + WIDTH / 15 + 43, position.y + HEIGHT / 10}, BLACK)
, _leftBox(Vector2{WIDTH / 15, HEIGHT / 15}, Vector2{position.x + (2 * (WIDTH / 15 + 43)), position.y + HEIGHT / 10}, BLACK)
, _rightBox(Vector2{WIDTH / 15, HEIGHT / 15}, Vector2{position.x + (3 * (WIDTH / 15 + 43)), position.y + HEIGHT / 10}, BLACK)
, _BombBox(Vector2{WIDTH / 14, HEIGHT / 15}, Vector2{position.x + (4 * (WIDTH / 15 + 43) + 150), position.y + HEIGHT / 10}, BLACK)
, _name()
, _up(265)
, _down(264)
, _left(263)
, _right(262)
, _bomb(KEY_SPACE)
, _box()
, name_clicked(false)
, up_clicked(false)
, down_clicked(false)
, right_clicked(false)
, bomb_clicked(false)
, _buttons()
, _font()
, _type(none)
{
    _nameBox.setColor(BLACK);
    _upBox.setColor(BLACK);
    _downBox.setColor(BLACK);
    _leftBox.setColor(BLACK);
    _rightBox.setColor(BLACK);
    _BombBox.setColor(BLACK);
    _box.height = _nameBox.getSize().y;
    _box.width = _nameBox.getSize().x;
    _box.y = _nameBox.getPosition().y;
    _box.x = _nameBox.getPosition().x;
    _font = LoadFont("font_gamer");
    _buttons[ia] = std::unique_ptr<Button>(new Button
    (std::pair<float, float>(position.x + WIDTH / 3 + 50, position.y), {100.0f, 70.0f}, " ia ",
    [&]() { _type = ia ;}));
    _buttons[player] = std::unique_ptr<Button>(new Button
    (std::pair<float, float>(position.x + WIDTH / 3 + 190, position.y), {280.0f, 70.0f}, " player ",
    [&]() { _type = player ;}));
}

Choose::~Choose()
{
}

void Choose::action_buttons()
{
    if (_raylib->isMousePressed())
        for (auto &it : _buttons)
            if (it.second->isClicked(_raylib->getMousePosition()))
                it.second->action();
}

void Choose::draw_buttons()
{
    Color color = BLACK;
    for (auto &it : _buttons)
    {
        color = (it.first == _type) ? RED : BLACK;
        if (_raylib->getMousePosition().first >= it.second->getPosition().first && _raylib->getMousePosition().first <= it.second->getPosition().first + it.second->getSize().first &&
            _raylib->getMousePosition().second >= it.second->getPosition().second && _raylib->getMousePosition().second <= it.second->getPosition().second + it.second->getSize().second) {
            _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, RED);
        }
        else
            _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, color);
        _raylib->drawText(it.second->getPosition(), it.second->getText(), WHITE, _font, 80, 2);
    }
}

void Choose::reset_box(const ry::v2d::Rectangle &box) noexcept
{
    _box.height = box.getSize().y;
    _box.width = box.getSize().x;
    _box.y = box.getPosition().y;
    _box.x = box.getPosition().x;
}

void Choose::handle_command() noexcept
{
    uint16_t key;

    if (_type != player)
        return;
    if (up_clicked || down_clicked || left_clicked || right_clicked || bomb_clicked == true)
        key = GetKeyPressed();
    if (up_clicked == true)
        _up = (key > 0 && key != _down && key != _left && key != _right) ? key : _up;
    if (down_clicked == true)
        _down = (key > 0 && key != _up && key != _left && key != _right) ? key : _down;
    if (left_clicked == true)
        _left = (key > 0 && key != _down && key != _up && key != _right) ? key : _left;
    if (right_clicked == true)
        _right = (key > 0 && key != _down && key != _left && key != _up) ? key : _right;
    if (bomb_clicked == true) 
        _bomb = (key > 0 && key != _down && key != _left && key != _up && key != _right) ? key : _bomb;
}

void Choose::handle_click() noexcept
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        reset_box(_nameBox);
        name_clicked = CheckCollisionPointRec(GetMousePosition(), _box);
        reset_box(_upBox);
        up_clicked = CheckCollisionPointRec(GetMousePosition(), _box);
        reset_box(_downBox);
        down_clicked = CheckCollisionPointRec(GetMousePosition(), _box);
        reset_box(_leftBox);
        left_clicked = CheckCollisionPointRec(GetMousePosition(), _box);
        reset_box(_rightBox);
        right_clicked = CheckCollisionPointRec(GetMousePosition(), _box);
        reset_box(_BombBox);
        bomb_clicked = CheckCollisionPointRec(GetMousePosition(), _box);
    }
}

void Choose::handle_writing()
{
    char key;

    if (name_clicked == false)
        return handle_command();
    key = GetCharPressed();
    for (; _name.size() < NAME_MAX &&  key > 0; key = GetCharPressed()) {
        if (key >= 32 && key <= 125 && key != ' ')
            _name.push_back(key);
    }
    if (IsKeyPressed(KEY_BACKSPACE) && _name.empty() == false)
            _name.pop_back();
}

void Choose::draw()
{
    _nameBox.draw((name_clicked == true) ? RED : BLACK);
    DrawText(_name.c_str(), _nameBox.getPosition().x + 5, _nameBox.getPosition().y + 10, 40, RED);
    if (_type == player) {
        _upBox.draw((up_clicked == true) ? RED : BLACK);
        DrawTextCodepoint(_font, _up, _upBox.getPosition(), 40, RED);
        _downBox.draw((down_clicked == true) ? RED : BLACK);
        DrawTextCodepoint(_font, _down, _downBox.getPosition(), 40, RED);
        _leftBox.draw((left_clicked == true) ? RED : BLACK);
        DrawTextCodepoint(_font, _left, _leftBox.getPosition(), 40, RED);
        _rightBox.draw(right_clicked == true ? RED : BLACK);
        DrawTextCodepoint(_font, _right, _rightBox.getPosition(), 40, RED);
        DrawText("BOMB: ", _BombBox.getPosition().x - 150, _BombBox.getPosition().y + 10, 40, RED);
        _BombBox.draw(bomb_clicked == true ? RED : BLACK);
        DrawTextCodepoint(_font, _bomb, _BombBox.getPosition(), 40, RED);
    }
    draw_buttons();
}

uint16_t Choose::getKeyUp() const noexcept
{
    return _up;
}

uint16_t Choose::getKeyDown() const noexcept
{
    return _down;
}

uint16_t Choose::getKeyLeft() const noexcept
{
    return _left;
}

uint16_t Choose::getKeyRight() const noexcept
{
    return _right;
}

uint16_t Choose::getKeyBomb() const noexcept
{
    return _bomb;
}

Choose::Personnage Choose::getType() const noexcept
{
    return _type;
}

const std::string &Choose::getName() noexcept
{
    return _name;
}

void Choose::run()
{
    // ballPosition = GetMousePosition();
}