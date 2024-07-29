/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Button
*/

#include "../include/Button.hpp"
#include "../include/Exception.hpp"

Button::Button(std::pair<float, float>pos, std::pair<float, float>size, std::string text, std::function<void()> funct, std::string texture) :
_pos(pos), _size(size), _text(text), _funct(funct)
{
    rec.x = _pos.first;
    rec.y = _pos.second;
    rec.width = _size.first;
    rec.height = _size.second;
    std::string path = folder_assets + texture;
    if (!texture.empty())
        LoadTextureButton(path);
}

Button::~Button()
{
    if (_texture.id > 0)
        UnloadTexture(_texture);
}

std::pair<float, float> Button::getSize()
{
    return _size;
}

std::pair<float, float> Button::getPosition()
{
    return _pos;
}

void Button::setSize(std::pair<float, float>size)
{
    _size = size;
}

void Button::setPosition(std::pair<float, float>pos)
{
    _pos = pos;
}

std::string Button::getText()
{
    return _text;
}

bool Button::isClicked(std::pair<float, float> mouse_position)
{
    if (mouse_position.first >= _pos.first && mouse_position.first <= _pos.first + _size.first &&
        mouse_position.second >= _pos.second && mouse_position.second <= _pos.second + _size.second) {
        return true;
        }
    return false;
}

void Button::action()
{
    _funct();
}

Rectangle Button::getRectangle()
{
    return rec;
}

void Button::LoadTextureButton(std::string &texture)
{
    Image image = LoadImage(texture.c_str());
    try {
        if (image.data == NULL)
            throw Exception("error in loading file: " + texture);
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    ImageResize(&image, _size.first, _size.second);
    _texture = LoadTextureFromImage(image);
}

Texture2D Button::getTexture()
{
    return _texture;
}