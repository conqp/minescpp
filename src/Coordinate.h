//
// Created by rne on 27.12.21.
//

#pragma once

#include <vector>

class Coordinate {
public:
    short x;
    short y;
    Coordinate(short x, short y);
    [[nodiscard]] std::vector<Coordinate> getNeighbors() const;
};


