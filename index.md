---
layout: home 
---

Welcome to my AStar Algorithm C++ blog

This project implements C++ code to create a pathfinding algorithm using a 2d grid with obstacles with an aim to find the shortest path from the starting point to the end point using a heuristic based search, this was developed incrementally, building on the knowledge gained and progress made. 

**Requirements**
**Modern C++**:
modern C++ coding techniques were used in the making of this project such as
 auto: Used when iterating and when storing iterator results (e.g. auto it = gScore.find(next)) 
  to avoid repeating verbose type names and keep the code readable.

 Range-based for loops: Used in Grid::print() to work through rows and cells 
  without manual index management.

 std::vector: Used for the grid storage and for returning the path. I use this instead of raw 
  arrays because it manages its own memory and can be returned from functions.

 std::priority_queue: Used for the open set so the node with the lowest f-score is 
  always chosen next, which is what A* requires.

 std::unordered_map and std::unordered_set: Used for gScore, cameFrom, and the closed 
  set because lookups are O(1) on average, which keeps the algorithm working efficiently.

 std::array<int, 4>: Used for the direction arrays dr and dc instead of C-style arrays. 
  std::array has the same performance but is a proper C++ type with bounds.

 noexcept: used for functions like rows(), cols(), and operator== that are
  not going to throw.

 constexpr: Used for Grid::Free and Grid::Obstacle so these values are resolved at 
  compile time rather than stored as runtime variables.

 inline: Used for the manhattan() function in Heuristic.h so it can be used in a 
  header and used across multiple files without causing multiple definition errors.

**Object oriented design**:
Grid: Manages the map data. It keeps the internal cell storage private and exposes only 
what other classes need: setCell(), isObstacle(), inBounds(), and print(). 
Nothing outside Grid can corrupt the grid.

Point: A simple coordinate type with a row/column position on the grid. 
Also uses operator== so two points can be compared, the solver uses this 
to check if it has reached the goal.

AStarSolver: The pathfinding engine. Takes a Grid, a start Point, and a goal Point, 
and returns the shortest path as a vector of Points. It only calls grid.inBounds() 
and grid.isObstacle(), it does not use the grid internals directly.

Heuristic: Calculates Manhattan distance between 
two Points. It is separated from the solver so the heuristic could be swapped out 
without changing the algorithm.

**Use of STL**
std::vector: for Grid storage
std::priority_queue: for open set
std::unordered_map: for g scores and path reconstruction
std::unordered_set: for closed set

**A* implementation**
The map is grid based, and obstacles are supported, movement is 4 directional, the Manhattan formula is used to calculate the distance between 2 points on a grid. The shortest path is returned, if no path exists it returns empty.

**Use of Point Hash**
C++ unordered_map and unordered_set need a hash function for any custom key type. 
Since Point is a struct I made myself, C++ has no built-in way to hash it, so I 
wrote PointHash to provide one.

The hash combines the row and column values using XOR and a large magic number 
(0x9e3779b9), which comes from the golden ratio. This spreading technique reduces 
hash collisions, so two different Points are not going to produce the same hash 
value and end up in the same bucket. Without a hash, the algorithm would slow down.



**week 1**
Researching the project, finding out the requirements and researching the A* algorithm, I watched several 
YouTube videos of how A* works, I learned that it uses a heuristic to estimate the remaining distance to the 
goal, which makes it faster because it does not travel in the wrong 
direction.
I prompted ChatGPT to explain to me what A* algorithm is and how it could be implemented in a C++ pathfinding project to get a better idea of how the framework operates and how the skeleton of the project would look.

**week 2**
Sorting out file structure and creating the files I think I will need to get the algorithm working:
the project would use a type to represent a grid position (Point), a location 
to store and query the grid (Grid), the algorithm itself (AStarSolver), and a 
heuristic function. Splitting these into separate files makes the project goal easier to understand.

**week 3**
Researched what responsibilities each file should have before writing  code. I looked into how std::priority_queue works and why it is the 
right container for A*. It always gives the element with the lowest value 
first, which is what the open set needs. I also researched 
std::unordered_map and std::unordered_set and found that they need a hash 
function for any custom type used as a key. This research would be useful when building the algorithm.

**week 4**
Created a smoke test that ensures my files are building correctly and the control flow works as intended and the core matrix lifecycle works.

**week 5**
Populated other files with data that allows matrix output capability and prints out a grid to work as a smoke test, this will allow me to build upon a solid 
base as I progress.

**week 6**
Pushed most recent progress to GitHub that creates a 5x5 grid and prints it to the console.
Grid.h: holds cells_ using a vector
Point.h: Defines the point coordinate type for grid positions
Heuristic.h: Uses the Manhattan distance formula for movement up, down, left, right
AStarSolver.h: declares find path function, but I am not using it yet
Main.cpp: brings the program together and runs it as a smoke test and does not run any A* logic yet
Grid.cpp: Implements grid methods from Grid.h
AStar.cpp: will have the A* logic but has not been implemented at this time
I also had to put my work in a new project because the project files got corrupted after I tried to move the project to a different folder and push it to GitHub, and putting it in a fresh project fixed this problem.

Removed duplicate point reference in heuristic.h so there is only one point type in point.h and no more conflict with Point.h
<img width="621" height="256" alt="image" src="https://github.com/user-attachments/assets/6616a868-d9d4-4565-9f19-cbdb612e0ca8" />


**week 7**
Added in A* logic from GeeksForGeeks and tweaked it to make it compatible with my project: https://www.geeksforgeeks.org/dsa/a-search-algorithm/ also added a temporary test that tests the matrix for the location of number 1 in the matrix and if the number is out of bounds. I used ChatGPT to help me understand how the initial code functions and to gain an understanding of the changes that would have to be made to the template A* algorithm.

What I changed to fit my own design:
 The GeeksForGeeks version uses a flat array and integer cell IDs. I rewrote it to use a Point struct and Grid class instead.
 I replaced the open list with std::priority_queue using a LowestF 
  comparator so the node with the lowest f-score is always used first.
 I added early exit guards at the top of findPath() for out-of-bounds start/goal, I also added
  obstacles on start/goal, and start == goal.
 I kept the closed set as std::unordered_set with PointHash instead of using a
  boolean array because the grid size is not fixed.

**week 8**
Spent time going through the project understanding how it works.
Explanation of current setup:

GridPoint.h: It shows how a position is represented on the grid which is a 5x5 grid, it also enables C++ to compare 2 points because the A* solver needs to know if it has visited a position in the matrix already and to know what point is the end goal. PointHash creates a hash value for a Point, it needs PointHash to use Point as a key in an unordered_map or unordered_set, the file uses this logic to represent a location and compare locations.

Heuristic.h: Defines the Manhattan distance formula that is implemented in the A* logic, the Manhattan formula allows for movement straight up, down, left and right which works for a matrix. It is called a heuristic because a heuristic is an estimate of how far a node is from a goal. The inline keyword lets the function be defined in the header without causing multiple definition errors across source files.

AStarSolver.h: The class interface for the pathfinding engine. It declares a class called AStarSolver and exposes one public function:
std::vector<Point> findPath(const Grid& grid, Point start, Point goal) const;
It inputs a grid, a start point and a goal point.
It outputs a vector of points to make the path.
If there are no paths it returns an empty vector.
This file separates the interface from the implementation, the rest of the project can reference this file for details of the A* algorithm.

Object oriented design: Using it in a simple way by implementing classes and types with set responsibilities:
Grid: manages the map, also keeps data private and exposes methods such as setCell(), isObstacle(), inBounds(), print() so other parts of the project don't have an impact on the internal grid storage.
AStarSolver: manages the search.
Point: defines a coordinate.
The solver only needs to call grid.inBounds(), grid.isObstacle() so grid hides its structure and gives a clean interface.
To ensure correct pathfinding each move on the grid costs 1 and movement is up/down/left/right and the Manhattan distance formula never overestimates the remaining cost resulting in A* returning the shortest path.
This project represents a grid with obstacles and uses A* pathfinding algorithm with Manhattan distance heuristic to get and display the shortest path from a start point to a goal point.
I prompted ChatGPT to explain to me how my project works so I can compare my knowledge and view on the project as a whole to ChatGPT's take on the project, so I can possibly gain a better understanding of it and check if anything in the project needs to be addressed that I cannot see. This process gave me a better understanding of the project.

**week 9**
I added a dedicated Tests.cpp file with six test cases testing both normal operation 
and edge cases. Tests are separated into their own file rather than sitting in main() 
to keep the code modular and to make it easy to run or skip them.

Each test creates a Grid, sets up a scenario, runs the solver, and checks whether the 
result matches what is expected:

Test 1: Basic reachable path: Places three obstacles in a row across the middle of 
a 5x5 grid, leaving gaps at the sides. Checks that the solver finds a path from (0,0) 
to (4,4), and that the path starts and ends at the correct points.

Test 2: No path exists: Surrounds the goal cell (4,4) with obstacles on three sides, 
making it completely unreachable. Checks that the solver returns an empty vector instead 
of a wrong or partial path.

Test 3: Start equals goal: Sets start and goal to the same cell (2,2). The expected 
result is a path of length 1 containing only that point. This tests the early-exit 
guard at the top of findPath().

Test 4: Start out of bounds: Defines a start point with row -1, which is outside the 
grid. Checks that the solver returns empty without crashing. This tests the inBounds() 
guard.

Test 5: Goal out of bounds: Sets a goal at (10,10) on a 5x5 grid. It has the same purpose as 
Test 4 but for the goal side.

Test 6: Start on obstacle: Puts an obstacle at (0,0) and uses it as the start. 
Checks that the solver does not begin from an obstacle cell.

<img width="549" height="378" alt="image" src="https://github.com/user-attachments/assets/89df4672-1d6f-4524-be48-8684587ae370" />

These tests show that the algorithm handles failure cleanly and 
does not crash or return incorrect results when the input is incorrect. Writing them also revealed that my inBounds() check needed to handle negative row/col values, 
which I fixed in Grid.cpp.

**Week 10**
This week I added a visual representation of the path the A* algorithm takes when navigating through obstacles so the path it is taking is visually clearer. Previously the grid printed as 
0s and 1s and the path printed separately as a list of coordinates, which was harder to see the route the algorithm chose.
I found out from researching into the STL that unordered_set gives O(1) average lookup, which is 
better than looping through the path vector for every cell. I used the 
same PointHash I had already written for the A* solver, so I didn't need any new hashing logic.

The cppreference documentation covering unordered_set was helpful as it gave me an idea of how to implement:
std::unordered_set<Point, PointHash> pathCells(path.begin(), path.end()); to achieve the goal.
I prompted ChatGPT to confirm the lookup reasoning I was using made sense in case I was going down the incorrect route.

I added a new function printWithPath() to the Grid class that takes the path 
vector and prints the grid using three symbols:
- (*) = path cell
- (#) = obstacle
- (.) = free cell

The key design decision here was how to check whether each cell is on the path 
during printing. I convert 
the path vector into a std::unordered_set before printing so each lookup is O(1), 
making the overall print O(rows x cols) regardless of path length. I had to update main.cpp to call printWithPath() if a path is found, if not, it defaults to the regular print().
<img width="613" height="468" alt="image" src="https://github.com/user-attachments/assets/912ce782-67a3-4bbf-82e1-39ef9f1448d6" />


**References**

[1] GeeksforGeeks, "A* Search Algorithm," GeeksforGeeks. [Online]. Available: 
https://www.geeksforgeeks.org/dsa/a-search-algorithm/. [Accessed: Mar. 18, 2026].

[2] F. Dalwigk, "A* algorithm EASY explained (example)," YouTube. [Online]. 
Available: https://www.youtube.com/watch?v=kEY1OxOj_CY. [Accessed: Mar. 18, 2026].

[3] P. E. Hart, N. J. Nilsson, and B. Raphael, "A Formal Basis for the Heuristic 
Determination of Minimum Cost Paths," IEEE Transactions on Systems Science and 
Cybernetics, vol. 4, no. 2, pp. 100–107, 1968.

[4] Red Blob Games, "Introduction to A*," redblobgames.com. [Online]. Available: 
https://www.redblobgames.com/pathfinding/a-star/introduction.html. 
[Accessed: Mar. 18, 2026].

[5] cppreference.com, "std::unordered_set," cppreference.com. [Online]. Available: 
https://en.cppreference.com/w/cpp/container/unordered_set. [Accessed: Mar. 18, 2026].

[6] cppreference.com, "std::priority_queue," cppreference.com. [Online]. Available: 
https://en.cppreference.com/w/cpp/container/priority_queue. [Accessed: Mar. 18, 2026].

[7] cppreference.com, "std::unordered_map," cppreference.com. [Online]. Available: 
https://en.cppreference.com/w/cpp/container/unordered_map. [Accessed: Mar. 18, 2026].

[8] cppreference.com, "std::array," cppreference.com. [Online]. Available: 
https://en.cppreference.com/w/cpp/container/array. [Accessed: Mar. 18, 2026].

[9] B. Stroustrup, "C++11 FAQ," stroustrup.com. [Online]. Available: 
https://stroustrup.com/C++11FAQ.html. [Accessed: Mar. 18, 2026].

[10] Stack Overflow, "Magic number in boost::hash_combine," stackoverflow.com. 
[Online]. Available: 
https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine. 
[Accessed: Mar. 18, 2026].

[11] Boost, "Hash Combine," boost.org. [Online]. Available: 
https://www.boost.org/doc/libs/1_87_0/libs/container_hash/doc/html/hash.html#notes_hash_combine. 
[Accessed: Mar. 18, 2026].

**AI Tools**
The use of AI tools has been mentioned throughout the blog.
Any AI suggested code was understood and adapted to fit my own ideas and structure before being used. At no point did I get AI to give me the complete solution for the project.

Week 1: Asked ChatGPT to explain what the A* algorithm is and how it could be 
structured in a C++ project, to get a clearer picture of how the skeleton of 
the project would look before I started.

Week 7: Used ChatGPT to help me understand how the GeeksForGeeks A* code 
functions and what changes would need to be made to adapt it to my own file 
structure and design. I used it to 
understand the logic and then rewrote it to fit my Point struct, Grid class, 
and my own early exit guards.

Week 8: Prompted ChatGPT to explain how the project works as a whole so I 
could compare it my own understanding and check if anything had 
been missed or misunderstood.

Week 10: Used ChatGPT to confirm that my O(1) lookup reasoning for 
printWithPath() was correct before committing to the approach.
