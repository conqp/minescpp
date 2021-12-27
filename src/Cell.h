//
// Created by rne on 27.12.21.
//

#pragma once
#include <optional>
#include <string>

class Cell {
public:
    std::optional<bool> hasMine;
    bool marked;
    bool visited;
    Cell();
    [[nodiscard]] std::string toString(bool gameOver) const;
    bool toggleMarked();
};


