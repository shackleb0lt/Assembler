CC = gcc
CFLAGS = -Wall -g -std=gnu99

OBJS = assembler.o asm_parser.o
OBJ = *.obj

EXE = assembler 

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXE)

asm_parser.o: asm_parser.c asm_parser.h
	$(CC) $(CFLAGS) -c asm_parser.c

assembler.o: asm_parser.h assembler.c
	$(CC) $(CFLAGS) -c assembler.c

# main.o: main.c shell.h
# 	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJS)
	rm -f $(OBJ)
	rm -f $(EXE)