/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Choose
*/

#ifndef CHOOSE_HPP_
#define CHOOSE_HPP_

#include "raylib/Rectangle.hpp"
#include "Raylib.hpp"
#include "Character.hpp"
#include "Button.hpp"



class Choose {
    public:
        Choose(Vector2 position, Raylib &raylib);
        ~Choose();
        enum Personnage {
            ia,
            player,
            none
        };
        void handle_writing();
        void handle_click() noexcept;
        void handle_command() noexcept;
        void action_buttons();
        void draw_buttons();
        void reset_box(const ry::v2d::Rectangle &box) noexcept;
        uint16_t getKeyUp() const noexcept;
        uint16_t getKeyDown() const noexcept;
        uint16_t getKeyLeft() const noexcept;
        uint16_t getKeyRight() const noexcept;
        uint16_t getKeyBomb() const noexcept;
        Personnage getType() const noexcept;
        const std::string &getName() noexcept;
        void draw();
        void run();

    private:
        Vector2 _position;
        Raylib *_raylib;
        ry::v2d::Rectangle _nameBox;
        ry::v2d::Rectangle _upBox;
        ry::v2d::Rectangle _downBox;
        ry::v2d::Rectangle _leftBox;
        ry::v2d::Rectangle _rightBox;
        ry::v2d::Rectangle _BombBox;
        std::string _name;
        uint16_t _up;
        uint16_t _down;
        uint16_t _left;
        uint16_t _right;
        uint16_t _bomb;
        Rectangle _box;
        bool name_clicked;
        bool up_clicked;
        bool down_clicked;
        bool left_clicked;
        bool right_clicked;
        bool bomb_clicked;
        std::map<Personnage, std::unique_ptr<Button>> _buttons;
        Font _font;
        Personnage _type;

    protected:
};

#endif /* !CHOOSE_HPP_ */