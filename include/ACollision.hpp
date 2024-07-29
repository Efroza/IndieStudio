/*
** EPITECH PROJECT, 2022
** cross_platform
** File description:
** ACollision
*/

#ifndef ACOLLISION_HPP_
#define ACOLLISION_HPP_

#include "ICollision.hpp"

class ACollision : public ICollision
{
    public:
        ACollision(const Vector3 &position, bool destructible = true, bool ative = true, float radius = 0);
        ~ACollision();
        const Vector3 &getPosition() noexcept;
        virtual void setPosition(const Vector3 &position) noexcept;
        float getRadius() const noexcept;
        void setRadius(float radius) noexcept;
        void setType(int type) noexcept;
        int getType() const noexcept;
        bool getActive() const noexcept;
        void setActive(bool active) noexcept;
        bool isColliding(const ICollision *collision) const noexcept;
        void setCase(size_t y, size_t x) noexcept;
        ICollision *getBackground() const noexcept;
        void setBackground(ICollision *background) noexcept;
        void resetBackground(ICollision *new_background = nullptr) noexcept;
        void draw_background();
        void action_background();
        void setMap(std::vector<std::vector<std::unique_ptr<ICollision>>> &map);
        virtual std::vector<std::vector<std::unique_ptr<ICollision>>> *getMap() const noexcept;
        virtual bool isDestructible() const noexcept;
        virtual bool die();
        virtual void action() = 0;
        virtual void draw() = 0;
    protected:
        Vector3 _position;
        bool _active;
        float _radius;
        int _type;
        bool _destructible;
        size_t _case_y;
        size_t _case_x;
        ICollision *_background;
        std::vector<std::vector<std::unique_ptr<ICollision>>> *_map;

    private:
};

#endif /* !ACOLLISION_HPP_ */
