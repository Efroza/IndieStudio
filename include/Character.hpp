/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Character
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include "ACollision.hpp"
#include "Bomb.hpp"

enum movement_e {
    NOPE,
    RIGHT,
    LEFT,
    UP,
    DONW
};

class Character : public ACollision {
    public:
        Character(std::string model, std::string texture, std::string name = "", Vector3 position = {0}, char character = '1');
        ~Character();
        float getSpeed() const noexcept;
        void setSpeed(float speed) noexcept;
        size_t getNbrOfBomb() const noexcept;
        void setNbrOfBomb(size_t value) noexcept;
        size_t getFireOfBomb() const noexcept;
        void setFireOfBomb(size_t fire) noexcept;
        void setWallPass(bool pass) noexcept;
        bool getWallPass() const noexcept;
        std::string getName() const noexcept;
        void setName(std::string) noexcept;
        void setTouchUp(uint16_t up) noexcept;
        void setTouchDown(uint16_t down) noexcept;
        void setTouchLeft(uint16_t left) noexcept;
        void setTouchRight(uint16_t right) noexcept;
        void setTouchBomb(uint16_t bomb) noexcept;
        uint16_t getTouchUp() const noexcept;
        uint16_t getTouchDown() const noexcept;
        uint16_t getTouchLeft() const noexcept;
        uint16_t getTouchRight() const noexcept;
        uint16_t getTouchBomb() const noexcept;
        void setTexture(std::string);
        void move_up() noexcept;
        bool up_colliding() const noexcept;
        void move_left() noexcept;
        bool left_colliding() const noexcept;
        void move_right() noexcept;
        bool right_colliding() const noexcept;
        void move_down() noexcept;
        bool down_colliding() const noexcept;
        void action() override;
        void draw();
        void drop_bomb() noexcept;
        bool insert_bonus(std::unique_ptr<ICollision> &collision) noexcept;
        std::string getColor() const noexcept;
        char getCharacter() const noexcept;
        void setColor(std::string &color) noexcept;

    private:
        void move_up(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &up) noexcept;
        void move_left(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &left) noexcept;
        void move_right(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &right) noexcept;
        void move_down(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &down) noexcept;
        void replace_map(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &replace) noexcept;
        void animation() noexcept;
        bool pass_wall(std::unique_ptr<ICollision> &actual, std::unique_ptr<ICollision> &wall) noexcept;

    protected:
        std::string _name;
        Model _model;
        Texture2D _texture;
        ModelAnimation *_animation;
        std::string _color;
        unsigned int _animsCount = 1;
        int _animFrameCounter = 0;
        float _rotation = 130;
        Vector3 _mainRota = {170, 120, 150};
        float _speed = 1;
        movement_e _move;
        size_t _number_of_bomb = 1;
        size_t _fire_bomb;
        bool _wall_pass;
        uint16_t _up;
        uint16_t _down;
        uint16_t _left;
        uint16_t _right;
        uint16_t _bomb;
        char _character;
};

#endif /* !CHARACTER_HPP_ */