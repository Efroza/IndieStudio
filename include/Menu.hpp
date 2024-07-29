/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "Animation.hpp"
#include "Button.hpp"
#include <memory>

class Menu {
    public:
        Menu(Raylib*);
        ~Menu();
        void AnimationBeforeMenu();
        void LaunchMenu(Texture2D);
        void NotDoneYet();
        void helpMenu();
        std::map<std::string, Animation*>createAnimation(std::vector<std::string>, std::vector<int>, std::vector<Color>, std::vector<std::pair<float, float>>);
        void reset();
        void print_buttons(Font);
        void button_pressed(std::pair<float, float>);
        void quit();
        void launchGame();
        void optionMenu();
        void print_option_button(Font);
        void print_help_button(Font);
        void button_pressed_option(std::pair<float, float>);
        std::string remove_useless(std::string);
        void print_fps_button(Font);
        void draw_menu_option(Font, Texture2D, Font);
        void choose_player();
    protected:
    private:
        Raylib *_raylib;
        Animation *_cursor;
        Rectangle _rect_cursor;
        std::map<std::string, std::unique_ptr<Button>> _buttons;
        std::map<std::string, std::unique_ptr<Button>> _buttons_option;
        std::map<std::string, std::unique_ptr<Button>> _buttons_help;
        bool _menu;
};

#endif /* !MENU_HPP_ */
