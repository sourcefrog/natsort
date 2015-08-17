CFLAGS = -Wall -g -Werror

OBJS = strnatcmp.o natsort.o

.PHONY: clean test

natsort: $(OBJS)
	$(CC) -o $@ $(OBJS)

test: natsort
	@bash ./run-tests.bash

clean:
	rm natsort $(OBJS)
