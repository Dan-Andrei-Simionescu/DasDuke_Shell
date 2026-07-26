CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -D_GNU_SOURCE

TARGETS=DasDuke_Shell

build: $(TARGETS)

DasDuke_Shell: src/DasDuke_Shell.c
	$(CC) $(CFLAGS) src/DasDuke_Shell.c src/DDS.h src/colour.h src/DDS_functions.c -o $(TARGETS) -lreadline

run: build
	./DasDuke_Shell

clean: 
	rm -f $(TARGETS)
