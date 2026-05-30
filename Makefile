	CC=gcc
CFLAGS=-Iinclude -pthread

automotive_platform: src/main.c src/can_handler.c src/logic.c src/diagnostic.c
	$(CC) $^ -o automotive_platform $(CFLAGS)

clean:
	rm -f automotive_platform
