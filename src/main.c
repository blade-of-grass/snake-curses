#include "snake.h"
#include "map.h"
#include "genio.h"

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// refresh rate in milliseconds
#define REFRESH_RATE 64

void clean(IO* io);

int main(int argc, const char** argv) {

    IO* io;
    if ((io = ioini()) == NULL) {
        exit(0);
    }

    srand(time(NULL));

    int width, height;
    iodimens(io, &width, &height);

    MAP* map = map_init(width, height);
    SNAKE* snake = snake_init('O', (struct Point) { .x = width / 2, .y = height / 2 });

    enum Action action;
    int collided = 0;
    while ((action = ioin()) != QUIT && !collided) {

        snake_turn(snake, action);
        collided = snake_move(snake);

        int x, y;
        snake_get_head(snake, &x, &y);
        if (map_eat(map, x, y)) {
            snake_grow(snake);
        }

        snake_draw(snake, io);
        map_draw(map, io);

        ioflush();

        usleep(REFRESH_RATE * 1000);
    }

    // clean up our resources
    map_free(map);
    snake_free(snake);

    clean(io);
}

void clean(IO* io) {
    iofree(io);
    exit(0);
}
