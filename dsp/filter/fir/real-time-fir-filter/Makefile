.PHONY: all clean test
CC ?= cc
CFLAGS ?= -O3 -std=c99 -Wall -Wextra -Iinclude

LIB = lib/libfir.a
SRC = src/fir.c
OBJ = build/fir.o

EXE = bin/realtime_stdin
EXE_SRC = examples/realtime_stdin.c

TEST = bin/test_fir
TEST_SRC = tests/test_fir.c

all: $(LIB) $(EXE) $(TEST)

build:
	mkdir -p build bin lib

$(OBJ): $(SRC) | build
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ) | build
	ar rcs $@ $<

$(EXE): $(EXE_SRC) $(LIB) | build
	$(CC) $(CFLAGS) $< -Llib -lfir -o $@

$(TEST): $(TEST_SRC) $(LIB) | build
	$(CC) $(CFLAGS) $< -Llib -lfir -o $@

test: $(TEST)
	./$(TEST)

clean:
	rm -rf build bin lib
