#ifndef GENIO_H
#define GENIO_H

#include "common.h"

typedef struct genio IO;

IO* ioini();

void iofree(IO* self);

void iodraw(IO* self, int x, int y, int c);

void iodimens(IO* self, int* w, int* h);

void ioflush();

enum Action ioin();

#endif // GENIO_H
