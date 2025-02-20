LDFLAGS=-lssl -lcrypto
CFLAGS= 
CC=gcc

FORCE: ;

main: main.c base32.c
	$(CC) $^ -o $@ $(LDFLAGS)

test: base32.c test_base32.c test_entrypoint.c FORCE
	$(CC) base32.c base64.c test_*.c -o $@ -lcunit
	./test
