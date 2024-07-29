/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Win
*/

#ifndef WIN_HPP_
#define WIN_HPP_

#include <iostream>
#include "Raylib.hpp"
#include <math.h>
#include "Button.hpp"
#include <memory>

class Win {
    public:
        Win(Raylib *);
        ~Win();
        void screenWin(const std::string &, const std::string &);
        void draw_buttons(Font font);
        void action_buttons();
        void reset();
        void goMenu();
        void restart();

    private:
        Raylib *_raylib;
        Camera3D _camera;
        Texture2D _background;
        Model _model;
        ModelAnimation *_anims;
        unsigned int _animsCount;
        std::map<std::string, std::unique_ptr<Button>> _buttons;
        Font _font;
        bool end = false;
};

#endif /* !WIN_HPP_ */