#include "map.h"
#include <stdlib.h>

struct Map {
    int width;
    int height;
    int food_x;
    int food_y;
};

void map_set_food(MAP* self) {
    self->food_x = rand() % self->width;
    self->food_y = rand() % self->height;
}

MAP* map_init(int width, int height) {
    MAP* self = malloc(sizeof(MAP));
    self->width = width;
    self->height = height;
    map_set_food(self);

    return self;
}

void map_free(MAP* self) {
    free(self);
}

void map_draw(const MAP* self, IO* io) {
    iodraw(io, self->food_x, self->food_y, 'O');
}

int map_eat(MAP* self, int x, int y) {
    if (x == self->food_x && y == self->food_y) {
        map_set_food(self);
        return 1;
    }

    return 0;
}

int map_col(MAP* self, int x, int y) {
    return x < 0 || y <= 0 || x >= self->width || y > self->height;
}
