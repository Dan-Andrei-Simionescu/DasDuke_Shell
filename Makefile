CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -D_GNU_SOURCE

TARGETS=DasDuke_Shell

build: $(TARGETS)

DasDuke_Shell: DasDuke_Shell.c
	$(CC) $(CFLAGS) DasDuke_Shell.c -o $(TARGETS)

run: build
	./DasDuke_Shell

clean: 
	rm -f $(TARGETS)
