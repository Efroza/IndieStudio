/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include "Raylib.hpp"

class Animation {
    public:
        Animation(Texture2D, int, Color, std::pair<float, float>);
        ~Animation();
        Texture2D getTexture();
        void setFrameWidth(float);
        void setFrameHeight(float);
        void addToFrameWidth(float);
        void addToFrameHeight(float);
		float getFrameHeight(void);
        float getFrameWidth(void);
        float getMaxFrame(void);
        float getNbOfFrameWidth(void);
        float getNbOfFrameHeight(void);
        std::pair<int, int> getSizeTexture(void);
        std::pair<float, float> getPosition();
        void setPosition(std::pair<float, float>);
        void setColor(Color);
        Color getColor(void);

    private:
        Texture2D _texture;
        float _nb_frames_width;
        float _nb_frames_height;
        float _actual_frame_width;
        float _actual_frame_height;
        float _max_frame;
        float _position_x;
        float _position_y;
        Color _color;
};

#endif /* !ANIMATION_HPP_ */