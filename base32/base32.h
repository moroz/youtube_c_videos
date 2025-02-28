#ifndef BASE32_H
#define BASE32_H

#include <stddef.h>
#include <stdint.h>

#define BASE32_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"

void base32_encode(const uint8_t *src, char *dst, size_t len);

#define BASE32_INCORRECT_PADDING (-1)
#define BASE32_INCORRECT_SYMBOL (-2)

int base32_decode(const char *src, uint8_t *dst, size_t limit);

#endif
