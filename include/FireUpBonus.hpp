/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** FireUpBonus
*/

#ifndef FIREUPBONUS_HPP_
#define FIREUPBONUS_HPP_

#include "IBonus.hpp"

class FireUpBonus : public ACollision, public IBonus {
    public:
        FireUpBonus(Vector3);
        ~FireUpBonus();
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

#endif /* !FIREUPBONUS_HPP_ */
