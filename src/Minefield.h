//
// Created by rne on 27.12.21.
//

#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Cell.h"
#include "Coordinate.h"

class Minefield: public std::vector<std::vector<Cell>> {
private:
    unsigned short width;
    unsigned short height;
protected:
    [[nodiscard]] std::string stringify(Coordinate const & position, bool gameOver) const;
    std::vector<std::reference_wrapper<Cell>> uninitializedCells();
public:
    Minefield(unsigned short width, unsigned short height);
    [[nodiscard]] bool isInitialized() const;
    [[nodiscard]] bool sweepCompleted() const;
    [[nodiscard]] bool isOnField(Coordinate const & position) const;
    [[nodiscard]] Cell const & cellAt(Coordinate const & position) const;
    [[nodiscard]] std::vector<std::reference_wrapper<Cell const>> getNeighbors(Coordinate const & position) const;
    [[nodiscard]] unsigned short countSurroundingMines(Coordinate const & position) const;
    [[nodiscard]] std::string toString(bool gameOver) const;
    Cell & cellAt(Coordinate const & position);
    void setNoMineAt(Coordinate const & position);
    void populate(unsigned short mines);
    void initialize(Coordinate const & start, unsigned short mines);
    void toggleMarked(Coordinate const & position);
    void visit(Coordinate const & position);
};


