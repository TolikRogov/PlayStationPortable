// helpers.hpp
#pragma once
#include <unordered_set>
#include "Entity.hpp"

// Хеш-функция для Rect
struct RectHash {
    std::size_t operator()(const Rect& r) const {
        // Комбинируем x, y, w, h в один хеш
        return ((r.x * 73856093) ^ 
                (r.y * 19349663) ^ 
                (r.w * 83492791)) ^
                (r.h * 87578209);
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