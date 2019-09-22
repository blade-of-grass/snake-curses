#ifndef COMMON_H
#define COMMON_H

enum Action {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    QUIT,
    NOP,
};

struct Point {
    int x;
    int y;
};

static inline int point_eq(struct Point a, struct Point b) {
    return a.x == b.x && a.y == b.y;
}

static inline int clamp_max(int value, int max) {
    return value > max ? max : value;
}

#endif // COMMON_H
