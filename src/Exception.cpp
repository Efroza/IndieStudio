/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Exception
*/

#include "../include/Exception.hpp"

Exception::Exception(const std::string &message) : _message(message)
{
}

const char *Exception::what() const noexcept
{
    return _message.c_str();
}