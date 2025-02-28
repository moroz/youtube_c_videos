UNAME_S := $(shell uname -s)
ARCH := $(shell arch)

ifeq ($(UNAME_S),Darwin)
	ifeq ($(ARCH),arm64)
		OPENSSL_PREFIX := /opt/homebrew/opt/openssl@3
	else
		OPENSSL_PREFIX := /usr/local/opt/openssl@3
	endif
	CFLAGS += -I$(OPENSSL_PREFIX)/include
	LDFLAGS = -L$(OPENSSL_PREFIX)/lib -lssl -lcrypto
endif

ifeq ($(UNAME_S),Linux)
	LDFLAGS = -lssl -lcrypto
endif

FORCE: ;

main: main.c base32.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test: base32.c test_base32.c test_entrypoint.c FORCE
	$(CC) base32.c base64.c test_*.c -o $@ -lcunit
	./test
