.PHONY: clean

CC = gcc
CFLAGS = -Wall -Werror
DBGFLAGS = -g $(CFLAGS)

EXE = todo.out

$(EXE) : main.c
	$(CC) $(DBGFLAGS) $^ -o $(EXE)

clean :
	rm -f $(EXE)
