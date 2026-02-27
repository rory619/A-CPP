#pragma once
#include <cstdlib>
#include "Point.h"

struct Point {
    int r, c;
    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
};


inline int manhattan(const Point& a, const Point& b) {        //manhattan formuala to measure how far apart 2 grid cells are when you can only move up/down/left/right 
    return std::abs(a.r - b.r) + std::abs(a.c - b.c);
}
