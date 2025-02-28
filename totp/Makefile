CC=clang
LDFLAGS += -lcrypto -lssl

totp: main.c base32.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
