/* Rory O Loughlin
   2026
*/
#include <iostream>
#include <string>
#include <vector>
#include "Grid.h"



int main() {
    Grid grid(5, 5);
    grid.setCell(1, 1, 1);
    grid.print();
    return 0;
}