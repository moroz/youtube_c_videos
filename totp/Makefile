UNAME_S := $(shell uname -s)
ARCH := $(shell arch)
CC = clang

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

totp: main.c base32.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
