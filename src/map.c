#include "map.h"
#include <stdlib.h>

struct Food {
    struct Point pos;
    int skin;
};

struct Map {
    int width;
    int height;
    struct Food food;
};

void map_set_food(MAP* self) {
    self->food.skin = 'O';
    self->food.pos.x = rand() % self->width;
    self->food.pos.y = rand() % self->height;
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
    iodraw(io, self->food.pos.x, self->food.pos.y, self->food.skin);
}

int map_eat(MAP* self, struct Point pos) {
    if (point_eq(pos, self->food.pos)) {
        map_set_food(self);
        return 1;
    }

    return 0;
}

int map_col(MAP* self, struct Point pos) {
    return
        pos.x < 0 ||
        pos.y <= 0 ||
        pos.x >= self->width ||
        pos.y > self->height;
}
