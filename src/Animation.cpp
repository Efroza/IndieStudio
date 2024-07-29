/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Animation
*/

#include "../include/Animation.hpp"

Animation::Animation(Texture2D texture, int nb_of_frames, Color color, std::pair<float, float> position) :
_texture(texture), _color(color),_position_x(position.first), _position_y(position.second)
{
    _actual_frame_height = 0;
    _actual_frame_width = 0;
    _nb_frames_width = (float)_texture.width / nb_of_frames;
    _nb_frames_height = (float)_texture.height / nb_of_frames;
    _max_frame = (float)_texture.width / _nb_frames_width;
    
}

Animation::~Animation()
{
    if (_texture.id > 0)
        UnloadTexture(_texture);
}

Texture2D Animation::getTexture()
{
    return _texture;
}

void Animation::setFrameWidth(float nb)
{
	_actual_frame_width = nb;
}

float Animation::getFrameWidth(void)
{
    return _actual_frame_width;
}

void Animation::addToFrameWidth(float nb)
{
	_actual_frame_width += nb;
}

void Animation::setFrameHeight(float nb)
{
    _actual_frame_height = nb;
}

float Animation::getFrameHeight(void)
{
	return _actual_frame_height;
}

void Animation::addToFrameHeight(float nb)
{
    _actual_frame_height += nb;
}

void Animation::setColor(Color color)
{
    _color = color;
}

std::pair <float, float> Animation::getPosition()
{
    return std::make_pair(_position_x, _position_y);
}

void Animation::setPosition(std::pair<float, float> position)
{
    _position_x = position.first;
    _position_y = position.second;
}

float Animation::getMaxFrame(void)
{
    return _max_frame;
}

std::pair<int, int> Animation::getSizeTexture(void)
{
    return std::make_pair(_texture.width, _texture.height);
}

Color Animation::getColor(void)
{
    return _color;
}

float Animation::getNbOfFrameWidth(void)
{
    return _nb_frames_width;
}

float Animation::getNbOfFrameHeight(void)
{
    return _nb_frames_height;
}