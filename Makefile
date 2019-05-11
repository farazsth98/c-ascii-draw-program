CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi -lm -g
SIMPLE = -D SIMPLE
DEBUG = -D DEBUG
OBJ = main.o effects.o helper.o linked_list.o io.o plotter.o
OBJ_DEBUG = main.o effects.o helper.o linked_list.o io.o plotter_debug.o
OBJ_SIMPLE = main.o effects.o helper.o linked_list.o io.o plotter_simple.o
EXEC = TurtleGraphics
EXEC_DEBUG = TurtleGraphicsDebug
EXEC_SIMPLE = TurtleGraphicsSimple

all : $(EXEC) $(EXEC_SIMPLE) $(EXEC_DEBUG)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS) 

$(EXEC_SIMPLE) : $(OBJ_SIMPLE)
	$(CC) $(OBJ_SIMPLE) -o $(EXEC_SIMPLE) $(CFLAGS)

$(EXEC_DEBUG) : $(OBJ_DEBUG)
	$(CC) $(OBJ_DEBUG) -o $(EXEC_DEBUG) $(CFLAGS)

main.o : main.c effects.h helper.h linked_list.h plotter.h
	$(CC) -c main.c $(CFLAGS)

effects.o : effects.c effects.h
	$(CC) -c effects.c $(CFLAGS)

helper.o : helper.c helper.h
	$(CC) -c helper.c $(CFLAGS)

io.o : io.c io.h helper.h linked_list.h
	$(CC) -c io.c $(CFLAGS)

linked_list.o : linked_list.c linked_list.h
	$(CC) -c linked_list.c $(CFLAGS)

plotter.o : plotter.c plotter.h effects.h helper.h linked_list.h
	$(CC) -c plotter.c $(CFLAGS)

plotter_debug.o : plotter.c plotter.h effects.h helper.h linked_list.h
	$(CC) -c plotter.c -o plotter_debug.o $(CFLAGS) $(DEBUG)

plotter_simple.o : plotter.c plotter.h effects.h helper.h linked_list.h
	$(CC) -c plotter.c -o plotter_simple.o $(CFLAGS) $(SIMPLE)

clean :
	rm -rf $(OBJ) $(EXEC) $(OBJ_SIMPLE) $(EXEC_SIMPLE) $(OBJ_DEBUG) $(EXEC_DEBUG)
