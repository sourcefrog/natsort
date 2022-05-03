CFLAGS = -Wall -g -Werror

OBJS = strnatcmp.o natsort.o

.PHONY: analyze clean test

natsort: $(OBJS)
	$(CC) -o $@ $(OBJS)

test: natsort
	@bash ./run-tests.bash

analyze: clean
	scan-build --status-bugs make

clean:
	rm -f natsort $(OBJS)
