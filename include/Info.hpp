/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Info
*/

#ifndef INFO_HPP_
#define INFO_HPP_

    #define IS_BLOCK(info) info->isBlock() == false && info.isBomb() == false

class Info {
    public:
        Info() : _block(false), _bomb(false) {};
        ~Info() = default;
        void setBlock(bool);
        void setBomb(bool);
        bool isBlock() const;
        bool isBomb() const;
        bool isSol() const noexcept;

    protected:
    private:
        bool _block;
        bool _bomb;
};

#endif /* !INFO_HPP_ */
