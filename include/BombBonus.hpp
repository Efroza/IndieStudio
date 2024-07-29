/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** BombBonus
*/

#ifndef BOMBBONUS_HPP_
#define BOMBBONUS_HPP_

#include "IBonus.hpp"

class BombBonus : public ACollision, public IBonus{
    public:
        BombBonus(Vector3);
        ~BombBonus();
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

#endif /* !BOMBBONUS_HPP_ */
