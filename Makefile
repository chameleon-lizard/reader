all: reader

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2

reader: Makefile client.c
	$(CC) -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE) reader.c

clean:
	rm -f reader

run:
	./reader

