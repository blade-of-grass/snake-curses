#ifndef STRUCTS_H
#define STRUCTS_H

#include <ncurses.h>
#include "common.h"
#include "genio.h"

typedef struct Snake SNAKE;

struct Point {
    int x;
    int y;
};

SNAKE* snake_init(char skin, struct Point startPos);

void snake_free(SNAKE* self);

// move the snake
// dir: the direction to move the snake
void snake_turn(SNAKE* self, enum Action dir);

// move the snake
// return true if snake has collided with itself
int snake_move(SNAKE* self);

// grow the snake
void snake_grow(SNAKE* self);

// draw the snake
void snake_draw(const SNAKE* self, IO* io);

// get the head of the snake
void snake_get_head(const SNAKE* self, int* x, int* y);

// get the snakes current score
int snake_get_score(const SNAKE* self);

#endif // STRUCTS_H
