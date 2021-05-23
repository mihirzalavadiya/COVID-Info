CC = gcc
CFLAGS = -I.
DEPS = common.h

fileio.out: fileio.c
	$(CC) -w $< -o $@

main: Home.c display.c selectcountry.c insertfile.c
	$(CC) -w -o $@ $^ -pthread $(CFLAGS)

.PHONY: clean
clean:
	rm -f fileio.out main

.PHONY: all 
all:main fileio.out