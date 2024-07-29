/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** SpeedBonus
*/

#ifndef SPEEDBONUS_HPP_
#define SPEEDBONUS_HPP_

#include "IBonus.hpp"

class SpeedBonus : public ACollision, public IBonus {
    public:
        SpeedBonus(Vector3);
        ~SpeedBonus();
        void applyBonus(Character *) noexcept;
        void draw_background();
        void action_background();
        void draw();
        void action();
        void setTexture();

    protected:
    private:
        Texture2D _texture;
        Vector3 _position;
};

#endif /* !SPEEDBONUS_HPP_ */
