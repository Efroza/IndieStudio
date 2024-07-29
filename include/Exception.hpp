/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <iostream>
#include <string>

class Exception : public std::exception {
    public:
        Exception(const std::string &message);
        const char *what() const noexcept override;
    protected:
    private:
        std::string _message;
};

#endif /* !EXCEPTION_HPP_ */