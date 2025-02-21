#ifndef BASE32_H
#define BASE32_H

#include <stddef.h>
#include <stdint.h>

#define BASE32_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"

void base32_encode(const uint8_t *src, char *dst, size_t len);

#endif
