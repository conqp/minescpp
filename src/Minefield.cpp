//
// Created by rne on 27.12.21.
//

#include <algorithm>
using std::ranges::all_of;
using std::ranges::for_each;
#include <functional>
using std::reference_wrapper;
#include <sstream>
using std::stringstream;
#include <string>
using std::string;
using std::to_string;
#include <vector>
using std::vector;

#include "Cell.h"
#include "Minefield.h"
#include "SteppedOnMine.h"

Minefield::Minefield(unsigned short width, unsigned short height)
    : width(width), height(height)
{
    for (unsigned short y = 0; y < height; y++) {
        vector<Cell> row;
        for (unsigned short x = 0; x < width; x++)
            row.push_back(Cell());

        push_back(row);
    }
}

string Minefield::stringify(Coordinate const & position, bool gameOver) const
{
    auto const & cell = cellAt(position);

    if (!*cell.hasMine && (cell.visited || gameOver)) {
        auto mines = countSurroundingMines(position);
        if (mines > 0)
            return to_string(mines);
    }

    return cell.toString(gameOver);
}

vector<reference_wrapper<Cell>> Minefield::uninitializedCells()
{
    vector<reference_wrapper<Cell>> cells;

    for (auto & row : *this)
        for (auto & cell : row)
            if (!cell.hasMine.has_value())
                cells.push_back(cell);

    return cells;
}

bool Minefield::isInitialized() const
{
    return all_of(*this, [] (auto const & row) {
        return all_of(row, [] (auto const & cell) {
            return cell.hasMine.has_value();
        });
    });
}

bool Minefield::sweepCompleted() const
{
    return all_of(*this, [] (auto const & row) {
        return all_of(row, [] (auto const & cell) {
            return *cell.hasMine || cell.visited;
        });
    });
}

bool Minefield::isOnField(Coordinate const & position) const
{
    return position.x >= 0 && position.x < width && position.y >= 0 && position.y < height;
}

Cell const & Minefield::cellAt(Coordinate const & position) const
{
    return at(position.y).at(position.x);
}

Cell & Minefield::cellAt(Coordinate const & position)
{
    return at(position.y).at(position.x);
}

vector<reference_wrapper<Cell const>> Minefield::getNeighbors(Coordinate const & position) const
{
    vector<reference_wrapper<Cell const>> neighbors;

    for (auto const & neighbor : position.getNeighbors())
        if (isOnField(neighbor))
            neighbors.emplace_back(cellAt(neighbor));

    return neighbors;
}

unsigned short Minefield::countSurroundingMines(Coordinate const & position) const
{
    unsigned short mines = 0;
    for_each(getNeighbors(position), [&mines] (auto const & cell) mutable {
       if (cell.get().hasMine.has_value() && cell.get().hasMine.value())
           mines += 1;
    });
    return mines;
}

void Minefield::setNoMineAt(Coordinate const & position)
{
    auto & cell = cellAt(position);
    if (cell.hasMine.has_value())
        throw "Cell already initialized.";

    cell.hasMine = false;
}

void Minefield::populate(unsigned short mines)
{
    vector<reference_wrapper<Cell>> cells;

    while (mines--) {
        cells = uninitializedCells();
        unsigned short index = rand() % cells.size();
        auto & cell = cells[index].get();
        cell.hasMine = true;
    }

    for_each(uninitializedCells(), [] (auto & cell) { cell.get().hasMine = false; });
}

void Minefield::initialize(Coordinate const & start, unsigned short mines)
{
    setNoMineAt(start);
    populate(mines);
}

void Minefield::toggleMarked(Coordinate const & position)
{
    cellAt(position).toggleMarked();
}

void Minefield::visit(Coordinate const & position)
{
    if (!isOnField(position))
        return;

    auto & cell = cellAt(position);
    if (cell.visited || cell.marked)
        return;

    cell.visited = true;

    if (*cell.hasMine)
        throw SteppedOnMine();

    if (countSurroundingMines(position) == 0)
        for_each(position.getNeighbors(), [this] (auto const & neighbor) { visit(neighbor); });
}

string Minefield::toString(bool gameOver) const
{
    stringstream ss;

    for (unsigned short y = 0; y < height; y++) {
        for (unsigned short x = 0; x < width - 1; x++)
            ss << stringify(Coordinate(x, y), gameOver) << " ";

        ss << stringify(Coordinate(width - 1, y), gameOver) << "\n";
    }

    return ss.str();
}