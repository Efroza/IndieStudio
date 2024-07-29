/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** IA
*/

#include "../include/Wall.hpp"
#include "../include/IA.hpp"


IA::IA(std::string model, std::string texture, std::string name, Vector3 position, char character)
: Character(model, texture, name, position, character), _posGoalX(position.x), _posGoalY(position.y)
{
}

IA::~IA()
{
}

void IA::action()
{
    if (_map == nullptr)
		return;
    if (this->_case_x > this->_posGoalX  || _move == LEFT) {
        if (left_colliding() && _move == NOPE) {
            _posGoalX = _case_x;
            _posGoalY = _case_y;
            return newGoal();
        }
        move_left();
    }
    if (this->_case_x < this->_posGoalX ||_move == RIGHT) {
        if (right_colliding() && _move == NOPE) {
            _posGoalX = _case_x;
            _posGoalY = _case_y;
            return newGoal();
        }
        move_right();
    }
    if (this->_case_y > this->_posGoalY || _move == DONW) {
        if (down_colliding() && _move == NOPE) {
            _posGoalX = _case_x;
            _posGoalY = _case_y;
            return newGoal();
        }
        move_down();
    }
    if (this->_case_y < this->_posGoalY ||_move == UP) {
        if (up_colliding() && _move == NOPE) {
            _posGoalX = _case_x;
            _posGoalY = _case_y;
            return newGoal();
        }
        move_up();
    }

    if (this->_case_x == this->_posGoalX && this->_case_y == this->_posGoalY) {
        this->newGoal();
    }
}

void IA::newGoal() noexcept
{
    if (this->isDangerZone(this->_case_x, this->_case_y)) {
        this->newGoalDefense();
    } else {
        this->newGoalOffense();
    }
}

bool IA::isDangerZone(int x, int y) noexcept
{
    if (x < 0 || y < 0)
        return true;
    for (size_t yMap = 0; yMap < this->_map->size(); yMap++) {
        for (size_t xMap = 0; xMap < this->_map->at(y).size(); xMap++) {
            if (dynamic_cast<Bomb *>(this->_map->at(yMap).at(xMap).get()) != nullptr) {
                size_t range = dynamic_cast<Bomb *>(this->_map->at(yMap).at(xMap).get())->getRange();
                if (y == yMap && x >= xMap && x <= xMap + range) {
                    // std::cout << "danger\n";
                    return true;
                } else if (y == yMap && x <= xMap && x >= xMap - range) {
                    // std::cout << "danger\n";
                    return true;
                } else if (x == xMap && y >= yMap && y <= yMap + range) {
                    // std::cout << "danger\n";
                    return true;
                } else if (x == xMap && y <= yMap && y >= yMap - range) {
                    // std::cout << "danger\n";
                    return true;
                }
            }
        }
    }
    return false;
}

void IA::newGoalOffense() noexcept
{
    std::vector<int> dirX = {-1, 0, 1, 0};
    std::vector<int> dirY = {0, -1, 0, 1};
    int i = rand() % 4;
    int newX = this->_case_x + dirX[i];
    int newY = this->_case_y + dirY[i];

    if (!this->isDangerZone(newX, newY)) {
        if ((i == 0 && !left_colliding()) ||
        (i == 1 && !down_colliding()) ||
        (i == 2 && !right_colliding()) ||
        (i == 3 && !up_colliding())) {
            this->_posGoalX = this->_case_x + dirX[i];
            this->_posGoalY = this->_case_y + dirY[i];
            if (rand() % 3 == 0) {
            for (int a = 0; a < 4; a++) {
                if (dynamic_cast<Wall *>(this->_map->at(this->_case_y + dirY[a]).at(this->_case_x + dirX[a]).get()) != nullptr)
                    if (dynamic_cast<Wall *>(this->_map->at(this->_case_y + dirY[a]).at(this->_case_x + dirX[a]).get())->isDestructible() == true)
                    drop_bomb();
            }
            }
            // if (rand() % 8 == 0)
            //     drop_bomb();
        }
    }
}

void IA::newGoalDefense() noexcept
{
    std::vector<int> dirX = {-1, 0, 1, 0};
    std::vector<int> dirY = {0, -1, 0, 1};

    if (!this->isDangerZone(this->_case_x + dirX[IA_LEFT],
    this->_case_y + dirY[IA_LEFT])
    && !left_colliding()) {
        this->_posGoalX = this->_case_x + dirX[IA_LEFT];
        this->_posGoalY = this->_case_y + dirY[IA_LEFT];
    } else if (!this->isDangerZone(this->_case_x + dirX[IA_RIGHT],
    this->_case_y + dirY[IA_RIGHT])
    && !right_colliding()) {
        this->_posGoalX = this->_case_x + dirX[IA_RIGHT];
        this->_posGoalY = this->_case_y + dirY[IA_RIGHT];
    } else if (!this->isDangerZone(this->_case_x + dirX[IA_UP],
    this->_case_y + dirY[IA_UP])
    && !down_colliding()) {
        this->_posGoalX = this->_case_x + dirX[IA_UP];
        this->_posGoalY = this->_case_y + dirY[IA_UP];
    } else if (!this->isDangerZone(this->_case_x + dirX[IA_DOWN],
    this->_case_y + dirY[IA_DOWN])
    && !up_colliding()) {
        this->_posGoalX = this->_case_x + dirX[IA_DOWN];
        this->_posGoalY = this->_case_y + dirY[IA_DOWN];
    }
}
