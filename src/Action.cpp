//
// Created by rne on 27.12.21.
//

#include "Action.h"

#include <string>
using std::string;
#include <utility>
using std::move;

Action::Action(string action, Coordinate const & position)
    : action(move(action)), position(position)
{
}
