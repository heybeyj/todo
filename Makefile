.PHONY: clean debug

CC = gcc
CFLAGS = -Wall -Werror
DBGFLAGS = -g $(CFLAGS)

EXE = todo.out
DBGEXE = todo.dbg

$(EXE) : main.c
	$(CC) $(CFLAGS) $^ -o $(EXE)

clean :
	rm -f $(EXE)

debug : main.c
	$(CC) $(DBGFLAGS) $^ -o $(DBGEXE)
