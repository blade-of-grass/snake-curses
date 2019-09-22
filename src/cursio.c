#include "genio.h"

#include <curses.h>
#include <stdlib.h>
#include <stdio.h>

#define KEY_ESCAPE 27

struct genio {
    int width;
    int height;
};

IO* ioini() {

    /** * * * * * * * * * * * *
    *  curses initialization  *
    * * * * * * * * * * * * **/
    if (initscr() == NULL) {
        fprintf(stderr, "Error initializing ncurses\n");
        return NULL;
    }

    raw();      // disable input line buffering
    noecho();   // don't echo input
    nodelay(stdscr, true);
    keypad(stdscr, TRUE); // enable arrow keys
    curs_set(FALSE); // hide the cursor

    IO* self = malloc(sizeof(IO));
    getmaxyx(stdscr, self->height, self->width);

    return self;
}

void iofree(IO* self) {
    endwin();
    free(self);
}

void iodraw(IO* self, int x, int y, int c) {
    mvaddch(self->height - y, x, c);
}

void iodimens(IO* self, int* w, int* h) {
    *w = self->width;
    *h = self->height;
}

void ioflush() {
    refresh();
}

enum Action ioin() {

    switch(getch()) {

    case 'w':
    case KEY_UP:
        return NORTH;

    case 'd':
    case KEY_RIGHT:
        return EAST;

    case 's':
    case KEY_DOWN:
        return SOUTH;

    case 'a':
    case KEY_LEFT:
        return WEST;

    case 'q':
    case KEY_ESCAPE:
        return QUIT;

    default:
        return NOP;
    }
}
