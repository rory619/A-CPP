#pragma once
#include <vector>
#include "Point.h"

class Grid;
struct Point;


class AStarSolver {
public:
    // Returns the path from start -> goal
    // Returns empty vector if no path.
    std::vector<Point> findPath(const Grid& grid, Point start, Point goal) const;
};
