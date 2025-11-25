CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -O2

BASE=src/labyrinth.c
P1=patches/1.patch
P2=patches/2.patch
P3=patches/3.patch

all: labyrinth0 labyrinth1 labyrinth2 labyrinth3

labyrinth0: $(BASE)
	$(CC) $(CFLAGS) $< -o $@

labyrinth1.c: $(BASE) $(P1)
	cp $(BASE) labyrinth1.c
	patch -s labyrinth1.c < $(P1)

labyrinth1: labyrinth1.c
	$(CC) $(CFLAGS) labyrinth1.c -o $@

labyrinth2.c: labyrinth1.c $(P2)
	cp labyrinth1.c labyrinth2.c
	patch -s labyrinth2.c < $(P2)

labyrinth2: labyrinth2.c
	$(CC) $(CFLAGS) labyrinth2.c -o $@

labyrinth3.c: labyrinth2.c $(P3)
	cp labyrinth2.c labyrinth3.c
	patch -s labyrinth3.c < $(P3)

labyrinth3: labyrinth3.c
	$(CC) $(CFLAGS) labyrinth3.c -o $@

run: all
	./labyrinth0
	./labyrinth1 10
	./labyrinth2 "_@" 8
	./labyrinth3 42 ".#" 10
	./labyrinth3 43 ".#" 10
	./labyrinth3 42 ".#" 10

clean:
	rm -f labyrinth1.c labyrinth2.c labyrinth3.c labyrinth0 labyrinth1 labyrinth2 labyrinth3

.PHONY: all run clean
