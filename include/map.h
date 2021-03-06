#ifndef MAP_H
#define MAP_H

#include "common.h"
#include "genio.h"

typedef struct Map MAP;

MAP* map_init(int width, int height);

void map_free(MAP* map);

void map_draw(const MAP* map, IO* io);

int map_eat(MAP* map, struct Point pos);

int map_col(MAP* map, struct Point pos);

#endif // MAP_H
