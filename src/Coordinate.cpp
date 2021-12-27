//
// Created by rne on 27.12.21.
//

#include <vector>
using std::vector;

#include "Coordinate.h"

Coordinate::Coordinate(short x, short y)
    : x(x), y(y)
{
}

vector<Coordinate> Coordinate::getNeighbors() const
{
    vector<Coordinate> neighbors;

    for (short dx = -1; dx <= 1; dx++)
        for (short dy = -1; dy <= 1; dy++)
            if (!((dx == 0) && (dy == 0)))
                neighbors.emplace_back(x + dx, y + dy);

    return neighbors;
}
