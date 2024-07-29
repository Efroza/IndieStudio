/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Pause
*/

#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include <iostream>
#include "Raylib.hpp"
#include <functional>
#include <memory>
#include <fstream>
#include <math.h>
#include "Button.hpp"

class Pause {
    public:
        Pause(Raylib *, std::function<void(std::string &)>, std::function<void()>, std::function<void(bool)>);
        ~Pause();
        bool screenPause();
        void fillButtonPause();
        void printButtonsPause(Font);
        void printButtonsBefore(Font);
        void actionButtonBefore();
        void actionButton();
        std::string remove_useless(std::string);
        void drawPauseButton(Font music, Font font, Texture2D background);
        void insertButton(std::string, std::pair<float, float>, std::pair<float, float>, std::string, std::function<void()>);
        float getHeightLastButton() const noexcept;
        bool beforeGame();
        std::string getFirstLastButton() const noexcept;

    private:
        std::map<std::string, std::unique_ptr<Button>> _buttons;
        std::map<std::string, std::unique_ptr<Button>> _buttons_select;
        Raylib *_raylib;
        std::function<void(std::string &)> _loadGame;
        std::function<void()> _saveGame;
        std::function<void(bool)> _draw;
        bool _load_save = false;
        Texture2D _background;
        Font _font;
        Font _music;
        bool _done = false;
        Texture2D _background_load;
        bool _quit = false;
        bool _new_game = false;
};

#endif /* !PAUSE_HPP_ */