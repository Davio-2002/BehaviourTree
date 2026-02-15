#pragma once

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
