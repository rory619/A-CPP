/* Rory O Loughlin
   2026
*/
#include "Grid.h"
#include <iostream>

Grid::Grid(int rows, int cols)
    : cells_(rows, std::vector<int>(cols, 0)) {
}

void Grid::setCell(int row, int col, int value) {
    if (!inBounds(row, col)) return;
    cells_[row][col] = value;
}

void Grid::print() const {
    for (const auto& row : cells_) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

bool Grid::inBounds(int row, int col) const {
    if (row < 0 || col < 0) return false;
    if (cells_.empty() || cells_[0].empty()) return false;
    return row < static_cast<int>(cells_.size())
        && col < static_cast<int>(cells_[0].size());
}