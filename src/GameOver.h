//
// Created by rne on 27.12.21.
//

#pragma once

#include <exception>
#include <string>


class GameOver: public std::exception {
private:
    std::string message;
    unsigned short returnCode;
public:
    GameOver(std::string  message, unsigned short returnCode);
    [[nodiscard]] char const * what() const noexcept override;
    [[nodiscard]] unsigned short getReturnCode() const noexcept;
};