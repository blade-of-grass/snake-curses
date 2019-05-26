CC = gcc
LIBS = -lncurses

# name of the executable file
EXEC = ./build/snake

# source/include/object directories
SDIR = ./src
IDIR = ./include
ODIR = ./build/obj

CFLAGS = -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -I$(IDIR)

_DEPS = snake.h map.h genio.h common.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJS = snake.o map.o cursio.o main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: build
.PHONY: compile
.PHONY: run
.PHONY: exec
.PHONY: clean

# create the build directory and compile the program
build:
	@mkdir -p $(ODIR)
	@make compile

# compile the program and link the ncurses library
compile: $(OBJS)
	$(CC) -o $(EXEC) $^ $(CFLAGS) $(LIBS)

# build and run the program
run:
	@make build
	@make exec

exec:
	$(EXEC)

# delete build files
clean:
	@rm -r build

