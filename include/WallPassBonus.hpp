/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** WallPassBonus
*/

#ifndef WALLPASSBONUS_HPP_
#define WALLPASSBONUS_HPP_

#include "IBonus.hpp"

class WallPassBonus : public ACollision, public IBonus {
    public:
        WallPassBonus(Vector3);
        ~WallPassBonus();
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

#endif /* !WALLPASSBONUS_HPP_ */
