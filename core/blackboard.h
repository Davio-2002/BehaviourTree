#pragma once

#include <ostream>

struct Vec2 {
    float x;
    float y;
};

struct BlackBoard {
    bool targetVisible{false};
    bool targetInRange{false};

    int ammo{10};

    Vec2 position{}; // NPC position
    Vec2 targetPos{};
    Vec2 patrolPoint{};
};

inline std::ostream &operator<<(std::ostream &os, const Vec2 &vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const BlackBoard &bb) {
    os << "{ visible=" << bb.targetVisible
       << ", inRange=" << bb.targetInRange
       << ", ammo=" << bb.ammo
       << ", pos=" << bb.position
       << ", target=" << bb.targetPos
       << ", patrol=" << bb.patrolPoint
       << " }";
    return os;
}
