CFLAGS = -Wall -g -Werror

natsort: strnatcmp.o natsort.o
	$(CC) -o $@ strnatcmp.o natsort.o