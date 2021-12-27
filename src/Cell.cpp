//
// Created by rne on 27.12.21.
//

#include <optional>
using std::nullopt;
#include <string>
using std::string;

#include "Cell.h"

Cell::Cell()
    : hasMine(nullopt), marked(false), visited(false)
{
}

string Cell::toString(bool gameOver) const
{
    if (visited)
        return *hasMine ? "*" : " ";

    if (marked)
        return gameOver ? (*hasMine ? "!" : "x") : "?";

    if (gameOver && *hasMine)
        return "o";

    return gameOver ? " " : "■";
 }

bool Cell::toggleMarked()
{
    if (visited)
        return false;

    marked = !marked;
    return true;
}
