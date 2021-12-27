//
// Created by rne on 27.12.21.
//

#include <string>
using std::string;
#include <utility>
using std::move;

#include "GameOver.h"

GameOver::GameOver(string  message, unsigned short returnCode)
    : message(move(message)), returnCode(returnCode)
{
}

char const *GameOver::what() const noexcept
{
    return message.c_str();
}

unsigned short GameOver::getReturnCode() const noexcept
{
    return returnCode;
}
