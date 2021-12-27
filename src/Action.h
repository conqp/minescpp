//
// Created by rne on 27.12.21.
//

#pragma once

#include <string>

#include "Coordinate.h"

class Action {
public:
    std::string action;
    Coordinate position;
    Action(std::string action, Coordinate const & position);
};


