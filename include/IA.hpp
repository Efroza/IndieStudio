/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** IA
*/

#ifndef IA_HPP_
#define IA_HPP_

#include "Character.hpp"

static const std::vector<std::pair<int, int>> Dir = {
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1}
};

enum direction_e {
    IA_LEFT,
    IA_UP,
    IA_RIGHT,
    IA_DOWN
};

class IA : public Character {
    public:
        IA(std::string model, std::string texture, std::string name, Vector3 position, char character = 'A');
        ~IA();
        void action() override;
        void newGoal() noexcept;
        bool isDangerZone(int x, int y) noexcept;
        void newGoalOffense() noexcept;
        void newGoalDefense() noexcept;

    protected:
    private:
        int _posGoalX;
        int _posGoalY;
};

#endif /* !IA_HPP_ */
