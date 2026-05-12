// helpers.hpp
#pragma once
#include <set>
#include "Entity.hpp"

struct CompareRect {
    bool operator()(const Rect& a, const Rect& b) const {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        if (a.w != b.w) return a.w < b.w;
        return a.h < b.h;
    }
};