all: reader

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2

reader: Makefile reader.c
	$(CC) -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE) reader.c

clean:
	rm -f reader

run:
	./reader

