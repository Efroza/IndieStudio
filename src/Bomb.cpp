/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Bomb
*/

#include "../include/Bomb.hpp"
#include "../include/Character.hpp"

Bomb::Bomb(float time_wanted, size_t *number_bomb, size_t range)
: _BombTimer(time_wanted)
, _number_bomb(number_bomb)
, _range(range)
, _sound()
, ACollision({0})
{
    if (_number_bomb != nullptr)
        *_number_bomb = *_number_bomb - 1;
    _sound = LoadSound("./assets/Small_Bomb_Explosion_Sound_Effect.wav");
    _sound.frameCount = 5;
    SetSoundVolume(_sound, 0.3);
}

Bomb::~Bomb()
{
}

float_t Bomb::getChrono() const noexcept
{
    return this->_BombTimer;
}

void Bomb::DropBomb()
{
	if (&_timer)
		_timer.lifetime = getChrono();
}

void Bomb::updateTimer()
{
    if (&_timer && _timer.lifetime > 0)
        _timer.lifetime -= GetFrameTime();
}

bool Bomb::timerDone()
{
    if (&_timer)
        return _timer.lifetime <= 0;
	return false;
}

void Bomb::draw()
{
    if (!timerDone()) {
        DrawSphere(_position, 0.5, DARKGRAY);
        return;
    }
    explosion();
    this->_active = false;
}

void Bomb::destroy_left() noexcept
{
    size_t counter = 0;
    ICollision *collision = nullptr;

    if (_map == nullptr || _case_y == 0 || _case_x == 0)
        return;
    for (size_t x = _case_x; x > 0; --x) {
        if (counter == _range + 1)
            break;
        collision = (*_map)[_case_y][x].get();
        if (collision == nullptr) {
            counter += 1;
            continue;
        }
        if (collision->isDestructible() == true) {
            collision->setActive(false);
            if (x != _case_x && dynamic_cast<Character *>(collision) == nullptr)
               return;
            continue;
        } else
            return;
        counter += 1;
    }
}

void Bomb::destroy_right() noexcept
{
    ICollision *collision = nullptr;

    if (_map == nullptr || _case_y == 0 || _case_x == 0)
        return;
    for (size_t x = _case_x; x < (*_map)[_case_y].size() - 1 && x <= _case_x + _range; ++x)
    {
        collision = (*_map)[_case_y][x].get();
        if (collision == nullptr)
            continue;
        if (collision->isDestructible() == true) {
            collision->setActive(false);
            if (x != _case_x && dynamic_cast<Character *>(collision) == nullptr)
               return;
            continue;
        }
        return;
    }
}

void Bomb::destroy_up() noexcept
{
    ICollision *collision = nullptr;

    if (_map == nullptr || _case_y == 0 || _case_x == 0)
        return;
    for (size_t y = _case_y; y < (*_map).size() - 1 && y <= _case_y + _range; ++y) {
        collision = (*_map)[y][_case_x].get();
        if (collision == nullptr)
            continue;
        if (collision->isDestructible() == true) {
            collision->setActive(false);
            if (y != _case_y && dynamic_cast<Character *>(collision) == nullptr)
               return;
            continue;
        }
        return;
    }
}

void Bomb::explosion() const noexcept
{
    for (size_t i = 0; i <= _range; ++i) {
        DrawCube(Vector3{(float)(_position.x), (float)(_position.y + i), (float)(_position.z)}, 1, 1, 0.5, ORANGE);
        DrawCube(Vector3{(float)(_position.x), (float)(_position.y - i), (float)(_position.z)}, 1, 1, 0.5, ORANGE);
        DrawCube(Vector3{(float)(_position.x + i), (float)(_position.y), (float)(_position.z)}, 1, 1, 0.5, ORANGE);
        DrawCube(Vector3{(float)(_position.x - i), (float)(_position.y), (float)(_position.z)}, 1, 1, 0.5, ORANGE);
    }
}

void Bomb::destroy_down() noexcept
{
    ICollision *collision = nullptr;

    if (_map == nullptr || _case_y == 0 || _case_x == 0)
        return;
    for (size_t y = _case_y; y > 0 && y >= _case_y -  _range; --y) {
        collision = (*_map)[y][_case_x].get();
        if (collision == nullptr)
            continue;
        if (collision->isDestructible() == true) {
            collision->setActive(false);
            if (y != _case_y && dynamic_cast<Character *>(collision) == nullptr)
               return;
        } else
            return;
    }
}

void Bomb::destroy() noexcept
{
    destroy_left();
    destroy_right();
    destroy_up();
    destroy_down();
}

void Bomb::action()
{
    updateTimer();
}

bool Bomb::die()
{
    destroy();
    if (_number_bomb != nullptr)
        *_number_bomb = *_number_bomb + 1;
    PlaySoundMulti(_sound);
    if (IsSoundPlaying(_sound) == false)
        return true;
    return false;
}

size_t Bomb::getRange() const noexcept
{
    return this->_range;
}