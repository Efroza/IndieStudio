/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** IButton
*/

#ifndef IBUTTON_HPP_
#define IBUTTON_HPP_

#include "Raylib.hpp"
#include <functional>

class Button {
    public:
        Button(std::pair<float, float>, std::pair<float, float>, std::string, std::function<void()>, std::string = "");
        ~Button();
        std::pair<float, float> getSize();
        std::pair<float, float> getPosition();
        void setSize(std::pair<float, float>);
        void setPosition(std::pair<float, float>);
        std::string getText();
        bool isClicked(std::pair<float, float> mouse_position);
        void action();
        Rectangle getRectangle();
        void LoadTextureButton(std::string &);
        Texture2D getTexture();

    protected:
        std::pair<float, float> _pos;
        std::pair<float, float> _size;
        std::string _text;
        std::function<void()> _funct;
        Rectangle rec;
        Texture2D _texture;
    private:
};

#endif /* !IBUTTON_HPP_ */
