/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "ACollision.hpp"

typedef struct {
    float lifetime;
} Timer;

class Bomb : public ACollision {
    public:
        Bomb(float time_wanted, size_t *number_bomb = nullptr, size_t range = 1);
        ~Bomb();
        void DropBomb();
        void updateTimer();
        bool timerDone();
        void setChrono(float) noexcept;
        float getChrono() const noexcept;
        Timer getTimer() noexcept;
        void destroy() noexcept;
        void destroy_left() noexcept;
        void destroy_right() noexcept;
        void destroy_up() noexcept;
        void destroy_down() noexcept;
        bool die() override;
        void draw();
        void explosion() const noexcept;
        void action() override;

        size_t getRange() const noexcept;

    protected:
    private:
        float _BombTimer;
        Timer _timer = {0};
        size_t *_number_bomb;
        size_t _range;
        Sound _sound;
};

#endif /* !BOMB_HPP_ */
