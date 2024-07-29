/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Character
*/

#include "../include/Character.hpp"
#include "../include/global.h"
#include "../include/raylib/Rectangle.hpp"
#include "../include/Exception.hpp"
#include "../include/IBonus.hpp"
#include "../include/Wall.hpp"

Character::Character(std::string model, std::string texture, std::string name, Vector3 position, char character) : _name(name)
, ACollision(position), _character(character)
{
    _model = LoadModel(model.c_str());
	_animation = LoadModelAnimations(model.c_str(), &_animsCount);
	_case_x = position.x / SIZE_MAP;
	_case_y = position.y / SIZE_MAP;
	_map = nullptr;
	_speed = 0.1;
	_move = NOPE;
	_color = texture;
	_number_of_bomb = 1;
	_fire_bomb = 1;
	_wall_pass = false;
	_up = KEY_UP;
	_down = KEY_DOWN;
	_left = KEY_LEFT;
	_right = KEY_RIGHT;
	_bomb = KEY_SPACE;
	setTexture(texture);
}

Character::~Character()
{
    for (unsigned int i = 0; i < _animsCount; i++) UnloadModelAnimation(_animation[i]);
    RL_FREE(_animation);
	if (_model.boneCount > 0)
		UnloadModel(_model);
	if (_texture.id > 0)
		UnloadTexture(_texture);
}
void Character::draw()
{
	DrawModelEx(_model, _position, _mainRota, _rotation, Vector3{PROFONDEUR, PROFONDEUR, PROFONDEUR}, WHITE);
}

float Character::getSpeed() const noexcept
{
    return _speed;
}

void Character::setSpeed(float speed) noexcept
{
    _speed = speed;
}

size_t Character::getNbrOfBomb() const noexcept
{
	return _number_of_bomb;
}

void Character::setNbrOfBomb(size_t value) noexcept
{
	_number_of_bomb = value;
}

size_t Character::getFireOfBomb() const noexcept
{
	return _fire_bomb;
}

void Character::setFireOfBomb(size_t fire) noexcept
{
	_fire_bomb = fire;
}

void Character::setWallPass(bool pass) noexcept
{
	_wall_pass = pass;
}

void Character::setTouchUp(uint16_t up) noexcept
{
	_up = up;
}
void Character::setTouchDown(uint16_t down) noexcept
{
	_down = down;
}
void Character::setTouchLeft(uint16_t left) noexcept
{
	_left = left;
}
void Character::setTouchRight(uint16_t right) noexcept
{
	_right = right;
}

void Character::setTouchBomb(uint16_t bomb) noexcept
{
	_bomb = bomb;
}

std::string Character::getName() const noexcept
{
    return _name;
}

void Character::setName(std::string name) noexcept
{
    _name = name;
}

void Character::setTexture(std::string texture)
{
    _texture = LoadTexture(texture.c_str());
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
}



void Character::animation() noexcept
{
	UpdateModelAnimation(_model, _animation[0], _animFrameCounter);
	_animFrameCounter++;
	if (_animFrameCounter >= _animation[0].frameCount)
		_animFrameCounter = 0;
}

void Character::replace_map(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &replace) noexcept
{
	if (_background == nullptr) {
		actual.swap(replace);
		return;
	}
	replace.reset(_background);
	actual.swap(replace);
	_background = nullptr;
}

void Character::move_up() noexcept
{
	if (_map == nullptr)
		return;
	move_up((*_map)[_case_y][_case_x], UP_SIDE((*_map), _case_x, _case_y));
}

bool Character::insert_bonus(std::unique_ptr<ICollision> &collision) noexcept
{
	IBonus *bonus = nullptr;

	bonus = dynamic_cast<IBonus *>(collision.get());
	if (bonus == nullptr)
		return false;
	bonus->applyBonus(this);
	collision.reset(nullptr);
	return true;
}

bool Character::pass_wall(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &wall) noexcept
{
	if (_wall_pass == false || wall->isDestructible() == false
	|| dynamic_cast<Wall *>(wall.get()) == nullptr)
		return false;
	actual->setBackground(wall.release());
	return true;
}

bool Character::up_colliding() const noexcept
{
	ICollision *collision;

	if (_case_y >= (*_map).size() - 1)
		return false;
	return isColliding((UP_SIDE((*_map), _case_x, _case_y)).get())
		|| (dynamic_cast<IBonus *>((UP_SIDE((*_map), _case_x, _case_y)).get()) != nullptr);

}

bool Character::right_colliding() const noexcept
{
	ICollision *collision;

	if (_case_x >= (*_map)[_case_y].size())
		return false;
	return  isColliding((RIGHT_SIDE((*_map), _case_x, _case_y)).get())
		|| (dynamic_cast<IBonus *>((RIGHT_SIDE((*_map), _case_x, _case_y)).get()) != nullptr);

}

void Character::move_left() noexcept
{
	if (_map == nullptr)
		return;
	move_left((*_map)[_case_y][_case_x], LEFT_SIDE((*_map), _case_x, _case_y));
}

bool Character::left_colliding() const noexcept
{
	ICollision *collision;

	if (_case_x == 0)
		return false;
	return isColliding((LEFT_SIDE((*_map), _case_x, _case_y)).get())
	|| (dynamic_cast<IBonus *>((LEFT_SIDE((*_map), _case_x, _case_y)).get()) != nullptr);
}

void Character::move_right() noexcept
{
	if (_map == nullptr)
		return;
	move_right((*_map)[_case_y][_case_x], RIGHT_SIDE((*_map), _case_x, _case_y));
}

void Character::move_up(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &up) noexcept
{
	if (up.get() == actual.get())
		return;
	if (_move != NOPE && _move != UP)
		return;
	if ((_move == UP || up_colliding() == false
	|| pass_wall(actual, up) || insert_bonus(up) == true))
	{
		animation();
		_rotation = -90;
		_mainRota = {-350, 330, 310};
		_position.y += _speed;
		if (_move == NOPE) {
			_move = UP;
			_case_y = _position.y - _speed + SIZE_MAP;
			replace_map(actual, up);
		} else if (_position.y >= _case_y) {
			_position.y = _case_y;
			_move = NOPE;
		}
	}
}

void Character::move_left(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &left) noexcept
{
	if (left.get() == actual.get())
		return;
	if (_move != NOPE && _move != LEFT)
		return;
	if ((_move == LEFT || left_colliding() == false
	|| pass_wall(actual, left) || insert_bonus(left) == true)) {
		animation();
		_position.x -= _speed;
		_rotation = 90;
		_mainRota = {340, -20, 10};
		if (_move == NOPE) {
			_move = LEFT;
			_case_x = _position.x + _speed - SIZE_MAP;
			replace_map(actual, left);
		} else if (_position.x <= _case_x) {
			_move = NOPE;
			_position.x = _case_x;
		}
	}
}


void Character::move_right(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &right) noexcept
{
	if (right.get() == actual.get())
		return;
	if (_move != NOPE && _move != RIGHT)
		return;
	if (_move == RIGHT || right_colliding() == false
	|| pass_wall(actual, right)|| insert_bonus(right) == true)
	{
		UpdateModelAnimation(_model, _animation[0], _animFrameCounter);
		_animFrameCounter++;
		if (_animFrameCounter >= _animation[0].frameCount)
			_animFrameCounter = 0;
		_position.x += _speed;
		_rotation = 180;
		_mainRota = {0, 250, 260};
		if (_move == NOPE) {
			_move = RIGHT;
			_case_x = _position.x - _speed + SIZE_MAP;
			replace_map(actual, right);
		} else if (_position.x >= _case_x ) {
			_position.x = _case_x;
			_move = NOPE;
		}
	}
}

void Character::move_down(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &down) noexcept
{
	if (down.get() == actual.get())
		return;
	if (_move != NOPE && _move != DONW)
		return;
	if (_move == DONW || down_colliding() == false
	|| pass_wall(actual, down)|| insert_bonus(down) == true) {
		UpdateModelAnimation(_model, _animation[0], _animFrameCounter);
		_animFrameCounter++;
		if (_animFrameCounter >= _animation[0].frameCount)
			_animFrameCounter = 0;
		_position.y -= _speed;
		_rotation = 90;
		_mainRota = {170, 120, 150};
		if (_move == NOPE) {
			_move = DONW;
			_case_y = _position.y + _speed - SIZE_MAP;
			replace_map(actual, down);
			return;
		} else if (_position.y <= _case_y) {
			_position.y = _case_y;
			_move = NOPE;
		}
	}
}

void Character::move_down() noexcept
{
	if (_map == nullptr)
		return;
	move_down((*_map)[_case_y][_case_x], DOWN_SIDE((*_map), _case_x, _case_y));
}

bool Character::down_colliding() const noexcept
{
	ICollision *collision;

	if (_case_y == 0)
		return false;
	return isColliding((DOWN_SIDE((*_map), _case_x, _case_y)).get())
	|| (dynamic_cast<IBonus *>((DOWN_SIDE((*_map), _case_x, _case_y)).get()) != nullptr);
}

void Character::drop_bomb() noexcept
{
	if (_number_of_bomb == 0 || getBackground() != nullptr)
		return;
	Bomb *bomb = new Bomb(2.0f, &_number_of_bomb, _fire_bomb);
	Vector3 position;

	position.y = _case_y;
	position.x = _case_x;
	position.z = getPosition().z;

	bomb->setPosition(position);
	bomb->setMap(*_map);
	bomb->setCase(_case_y, _case_x);
	bomb->DropBomb();
	setBackground(bomb);
}

void Character::action()
{
	if (_map == nullptr)
		return;
	if (IsKeyDown(_up) || _move == UP)
		move_up();
	if (IsKeyDown(_left) || _move == LEFT)
		move_left();
	if (IsKeyDown(_right) || _move == RIGHT)
		move_right();
	if (IsKeyDown(_down) || _move == DONW)
		move_down();
	if (IsKeyPressed(_bomb))
		drop_bomb();
}

std::string Character::getColor() const noexcept
{
	return _color;
}

bool Character::getWallPass() const noexcept
{
	return _wall_pass;
}

uint16_t Character::getTouchUp() const noexcept
{
	return _up;
}

uint16_t Character::getTouchDown() const noexcept
{
	return _down;
}

uint16_t Character::getTouchLeft() const noexcept
{
	return _left;
}

uint16_t Character::getTouchRight() const noexcept
{
	return _right;
}

uint16_t Character::getTouchBomb() const noexcept
{
	return _bomb;
}

char Character::getCharacter() const noexcept
{
	return _character;
}

void Character::setColor(std::string &color) noexcept
{
	setTexture(color);
	_color = color;
}