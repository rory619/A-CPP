---
layout: home 
---

Welcome to my AStar Algorithm C++ blog!




**week 1**
Researching the project, finding out the requirements and researching the A* algorithm

**week 2**
Sorting out file structure and creating the files I think I will need to get the algorithm working


**week 3**
Researching the purpose for each file and ensuring I understand what data each file should have 


**week 4**
Cereated a smoke test that ensures my files are building correctly and the control flow works as intended and the core matrix lifecycle works

**week 5**
populated other files with data that allows matrix output capability and prints out a grid to work as a smoke test


**week 6**
Pushed most recent progress to github that creates a 5x5 grid and prints it to the console
Grid.h: holds cells_ using a vector
Point.h: Defines the point coordinate type for grid positions
Heuristic.h: Uses the Manhattan distance formula for movement up, down, left, right
AStarSolver.h: declares find path function, but I am not using it yet
Main.cpp: brings the program together and runs it as a smoke test and doesnt run any A* logic yet
Grid.cpp: Implements grid methods from Grid.h
AStar.cpp: will have the A* logic but hasnt been implemented but has not been implemented at this time

Removed duplicate point reference in heuristic.h so theres only one point type in point.h and no more conflict with Point.h
<img width="621" height="256" alt="image" src="https://github.com/user-attachments/assets/6616a868-d9d4-4565-9f19-cbdb612e0ca8" />




**week 7**
added in A* logic from GeeksForGeeks and tweaked it to make it compatiple with my project: https://www.geeksforgeeks.org/dsa/a-search-algorithm/ also added a temporary test that tests the matrix for the location of number 1 in the matrix and if the number is out of bounds: Task
/ Develop a modern C++ console application to implement the A* pathfinding 
algorithm.
/* Rory O Loughlin
   2026
*/
#include "AStarSolver.h"
#include "Grid.h"
#include "Heuristic.h"
#include "GridPoint.h"

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>

namespace
{
    struct Node {
        Point p;
        int g;
        int f;
    };

    struct LowestF {
        bool operator()(const Node& a, const Node& b) const {
            return a.f > b.f;
        }
    };

    std::vector<Point> reconstructPath(
        const std::unordered_map<Point, Point, PointHash>& cameFrom,
        Point start,
        Point goal
    ) {
        std::vector<Point> path;
        Point current = goal;
        path.push_back(current);

        while (!(current == start)) {
            auto it = cameFrom.find(current);
            if (it == cameFrom.end()) {
                return {};
            }

            current = it->second;
            path.push_back(current);
        }

        std::reverse(path.begin(), path.end());
        return path;
    }
}

std::vector<Point> AStarSolver::findPath(const Grid& grid, Point start, Point goal) const
{
    if (!grid.inBounds(start.r, start.c) || !grid.inBounds(goal.r, goal.c)) {
        return {};
    }

    if (grid.isObstacle(start.r, start.c) || grid.isObstacle(goal.r, goal.c)) {
        return {};
    }

    if (start == goal) {
        return { start };
    }

    std::priority_queue<Node, std::vector<Node>, LowestF> open;
    std::unordered_set<Point, PointHash> closed;
    std::unordered_map<Point, int, PointHash> gScore;
    std::unordered_map<Point, Point, PointHash> cameFrom;

    gScore[start] = 0;
    open.push({ start, 0, manhattan(start, goal) });

    const int dr[4] = { -1, 1, 0, 0 };
    const int dc[4] = { 0, 0, -1, 1 };

    while (!open.empty()) {
        Node current = open.top();
        open.pop();

        if (closed.find(current.p) != closed.end()) {
            continue;
        }

        if (current.p == goal) {
            return reconstructPath(cameFrom, start, goal);
        }

        closed.insert(current.p);

        for (int i = 0; i < 4; ++i) {
            Point next{ current.p.r + dr[i], current.p.c + dc[i] };

            if (!grid.inBounds(next.r, next.c)) {
                continue;
            }

            if (grid.isObstacle(next.r, next.c)) {
                continue;
            }

            if (closed.find(next) != closed.end()) {
                continue;
            }

            int tentativeG = gScore[current.p] + 1;

            auto it = gScore.find(next);
            bool foundBetterPath = (it == gScore.end()) || (tentativeG < it->second);

            if (foundBetterPath) {
                cameFrom[next] = current.p;
                gScore[next] = tentativeG;

                int f = tentativeG + manhattan(next, goal);
                open.push({ next, tentativeG, f });
            }
        }
    }

    return {};
}

**week 8**
spent time goig through the project understanding how it works 
Explanation of current setup:

GridPoint.h: It portrays how a position is shown on the grid which is a 4x4 grid it also enables c++ to compare 2 points because the A* solver needs to know if it has visited a position in the matrix already and to know what point is the end goal. PointHash creates a hash value for a Point, it needs point Hash to use Point as a key in an unordered_map, or unordered_set, the file uses this logic to represent a location and compare locations

Heuristic.h: defines the Manhatten distance formula that is implemented in the A* logic, the Manhattan formula allows for movement staight up, down, left right which works for a marix. Its called heuristic because a heuristic is an estimate of how far a node is from a goal, inline lets the function to be defined in the header without causing several defenition errors across source files

AStarSolver.h: The class interface for the pathfinding engine. It declares a class called AStarSolver and exposes one public function:
std::vector<Point> findPath(const Grid& grid, Point start, Point goal) const;
It inputs a grid, a start point and a goal point
I outputs a vector of points to make the path
If there are no paths it returns an empty vector
this file seperates the interface from the implementation, the rest of the project can reference this file for details of the A* algorithm

Object oriented design: Using it in a simple way by implementing classes and types with set responsibilities:
Grid: manages the map, also keeps data private and exposes methods such as SetCell(), isObstacle(), inBounds(), print() so other parts of the project dont have an impact on the inernal grid storage
AStarSolver: manages the search
Point: defines a coordinate
The solver only needs to call grid.inBounds(), grid.isObstacle() so grid hides its structure and gives a clear inference
To ensure correct pathfinding each move on the grid costs 1 and movement is up/down/left/right and the manhattan distance formula never over estimates the the remaining cost resulting in A* returning the shortest path
This project represents a grid with obstacles and uses A* pathfinding algorithm with Manhattan distance heuristic to get and display the shortest path from a start point to a goal point

