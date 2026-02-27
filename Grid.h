#pragma once
#include <vector>

class Grid {
public:
    Grid(int rows, int cols);

    void setCell(int row, int col, int value);
    void print() const;

private:
    bool inBounds(int row, int col) const;

    std::vector<std::vector<int>> cells_;
}; 
