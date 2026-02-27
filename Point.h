#pragma once
#include <cstddef>
#include <functional>

// A simple row/col coordinate for a grid.
struct Point {
    int r = 0;
    int c = 0;

    bool operator==(const Point& other) const noexcept {
        return r == other.r && c == other.c;
    }
};

// Needed so Point can be used in unordered_map / unordered_set.
struct PointHash {
    std::size_t operator()(const Point& p) const noexcept {
        // Simple hash combine (works fine for grid coords).
        std::size_t h1 = std::hash<int>{}(p.r);
        std::size_t h2 = std::hash<int>{}(p.c);
        return h1 ^ (h2 + 0x9e3779b9u + (h1 << 6) + (h1 >> 2));
    }
};