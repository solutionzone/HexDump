CC= gcc
SRC=./dump.c ./dumptest.c
OUTPUT=./dumptest.exe
LIBS=
OBJ=

all:
	$(CC) $(SRC) -o $(OUTPUT) $(OBJ) $(LIBS)
