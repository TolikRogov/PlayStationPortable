// helpers.hpp
#pragma once
#include <unordered_set>
#include "Entity.hpp"

// Хеш-функция для Rect
struct RectHash {
    std::size_t operator()(const Rect& r) const {
        std::size_t h1 = std::hash<int>{}(r.x);
            std::size_t h2 = std::hash<int>{}(r.y);
            std::size_t h3 = std::hash<int>{}(r.w);
            std::size_t h4 = std::hash<int>{}(r.h);
            
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};

// Оператор равенства для Rect
struct RectEqual {
    bool operator()(const Rect& a, const Rect& b) const {
        return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h;
    }
};

// Алиас для удобства
using DirtyRectsSet = std::unordered_set<Rect, RectHash, RectEqual>;