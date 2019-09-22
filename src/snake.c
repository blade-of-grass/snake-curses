#include "snake.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

struct Snake {
    int skin;      // the character to draw the snake as
    enum Action dir;
    int len;        // length of the snake
    struct Point points[MAX_LENGTH]; // points that compose the snake
    struct Point trail;
};

const struct Point Direction[4] = {
    [NORTH] = { .x = 0, .y = 1  },
    [EAST]  = { .x = 1, .y = 0  },
    [SOUTH] = { .x = 0, .y = -1 },
    [WEST]  = { .x =-1, .y = 0  },
};

const enum Action Opposite[4] = {
    [NORTH] = SOUTH,
    [EAST] = WEST,
    [SOUTH] = NORTH,
    [WEST] = EAST,
};

SNAKE* snake_init(int skin, struct Point startPos) {
    SNAKE* self = malloc(sizeof(SNAKE));
    self->skin = skin;
    self->len = 3;

    memset(&self->points[0], 0, MAX_LENGTH * sizeof(struct Point));
    for (int i = 0; i < self->len; ++i) {
        self->points[i] = startPos;
        startPos.y -= 1;
    }

    return self;
}

void snake_free(SNAKE* self) {
    free(self);
}

void snake_turn(SNAKE* self, enum Action dir) {
    if (dir >= NORTH && dir <= WEST && dir != Opposite[self->dir]) {
        self->dir = dir;
    }
}

int snake_move(SNAKE* self) {
    self->trail = self->points[self->len - 1];

    struct Point new_head = self->points[0];
    struct Point direction = Direction[self->dir];
    new_head.x += direction.x;
    new_head.y += direction.y;

    // check for collisions
    for (int i = 3; i < self->len; ++i) {
        struct Point iter = self->points[i];

        if (new_head.x == iter.x && new_head.y == iter.y) {
            self->skin='x';
            return 1;
        }
    }

    // move the snake
    memcpy(&self->points[1], &self->points[0], self->len * sizeof(struct Point));
    self->points[0] = new_head;

    return 0;
}

void snake_grow(SNAKE* self) {
    if (self->len == MAX_LENGTH) {
        return;
    }

    self->points[self->len] = self->points[self->len - 1];
    ++self->len;
}

void snake_draw(const SNAKE* self, IO* io) {
    for(int i = 0; i < self->len; ++i) {
        struct Point p = self->points[i];
        iodraw(io, p.x, p.y, self->skin);
    }
    iodraw(io, self->trail.x, self->trail.y, ' ');
}

void snake_get_head(const SNAKE* self, int* x, int* y) {
    *x = self->points[0].x;
    *y = self->points[0].y;
}

int snake_get_score(const SNAKE* self) {
    return self->len - 1;
}
