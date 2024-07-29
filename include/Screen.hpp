/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Screen
*/

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include "Map.hpp"
#include "Character.hpp"
#include "Choose.hpp"

class Screen {
    public:
        Screen(Raylib &raylib, Map &map);
        ~Screen();
        void draw_buttons() const noexcept;
        void action_buttons();
        void handles_chooses() noexcept;
        void add_chooses() noexcept;
        void load_info() noexcept;
        void run();

    private:
        void write_text() const noexcept;
        void add_player(Choose &info, float pos_y, float pos_x) noexcept;
        void add_ia(Choose &info, float pos_y, float pos_x) noexcept;
    private:
        Raylib *_raylib;
        Map *_map;
        Font _font;
        Vector2 _position;
        size_t _size_y;
        std::vector<std::unique_ptr<Button>> _buttons;
        std::vector<std::unique_ptr<Choose>> _chooses;
        bool _is_running;

    protected:
};

#endif /* !SCREEN_HPP_ */
