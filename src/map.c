#include "map.h"
#include <stdlib.h>

struct Map {
    int width;
    int height;
    int fx;
    int fy;
};

void map_set_food(MAP* self) {
    self->fx = rand() % self->width;
    self->fy = rand() % self->height;
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
    iodraw(io, self->fx, self->fy, '@');
}

int map_eat(MAP* self, int x, int y) {
    if (x == self->fx && y == self->fy) {
        map_set_food(self);
        return 1;
    }

    return 0;
}
