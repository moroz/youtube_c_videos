#include "base32.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

void base32_encode_quantum(const uint8_t *src, char *dst, size_t len) {
  uint32_t hi = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
  uint32_t lo = (hi << 8) | src[4];

  dst[0] = BASE32_ALPHABET[hi >> 27 & 0x1F];
  dst[1] = BASE32_ALPHABET[hi >> 22 & 0x1F];
  dst[2] = BASE32_ALPHABET[hi >> 17 & 0x1F];
  dst[3] = BASE32_ALPHABET[hi >> 12 & 0x1F];
  dst[4] = BASE32_ALPHABET[hi >> 7 & 0x1F];
  dst[5] = BASE32_ALPHABET[hi >> 2 & 0x1F];

  dst[6] = BASE32_ALPHABET[lo >> 5 & 0x1F];
  dst[7] = BASE32_ALPHABET[lo & 0x1F];
}

void base32_encode(const uint8_t *src, char *dst, size_t len) {
  int si = 0, di = 0;

  int fullQuantums = (len / 5) * 5;

  while (si < fullQuantums) {
    base32_encode_quantum(&src[si], &dst[di], fullQuantums - si);
    si += 5;
    di += 8;
  }

  int remaining = len - fullQuantums;

  if (remaining == 0) {
    dst[di] = '\0';
    // no padding required
    return;
  }

  // depending on the remaining length, encode the rest of the
  // source
  uint32_t val = 0;

  switch (remaining) {
  case 4:
    val |= src[si + 3];
    dst[di + 6] = BASE32_ALPHABET[val << 3 & 0x1F];
    dst[di + 5] = BASE32_ALPHABET[val >> 2 & 0x1F];
    // fallthrough

  case 3:
    val |= src[si + 2] << 8;
    dst[di + 4] = BASE32_ALPHABET[val >> 7 & 0x1F];

  case 2:
    val |= src[si + 1] << 16;
    dst[di + 3] = BASE32_ALPHABET[val >> 12 & 0x1F];
    dst[di + 2] = BASE32_ALPHABET[val >> 17 & 0x1F];

  case 1:
    val |= src[si + 0] << 24;
    dst[di + 1] = BASE32_ALPHABET[val >> 22 & 0x1F];
    dst[di + 0] = BASE32_ALPHABET[val >> 27 & 0x1F];
  }

  // number of bytes already set by unpadded data
  int npad = (remaining * 8 / 5) + 1;
  for (int i = npad; i < 8; i++) {
    dst[di + i] = '=';
  }

  dst[di + 8] = '\0';
}

static uint8_t base32_decode_char(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A';
  }
  if (c >= '2' && c <= '7') {
    return 26 + c - '2';
  }
  return 0xFF; // error value
}

int base32_decode(const char *src, char *dst, size_t limit) {
  int n;            // total number of bytes decoded
  int dsti;         // current position in destination buffer
  bool end = false; // whether we have reached the end of input
  n = dsti = 0;

  memset(dst, 0, limit);

  while (*src != '\0' && !end) {
    uint8_t buf[8];
    int dlen = 8;

    for (int i = 0; i < 8;) {
      char c = *src;

      // Handle and validate padding
      if (c == '\0') {
        return BASE32_INCORRECT_PADDING;
      }

      src++;

      if (isspace(c)) {
        continue;
      }

      size_t len = strlen(src);
      if (c == '=' && i >= 2 && len < 8) {
        if ((len) + i < 8 - 1) {
          // not enough padding
          return BASE32_INCORRECT_PADDING;
        };

        for (int j = 0; j < 8 - 1 - i; j++) {
          if (len > j && src[j] != '=') {
            return BASE32_INCORRECT_PADDING;
          }
        }

        dlen = i;
        end = true;

        if (dlen == 1 || dlen == 3 || dlen == 6) {
          return BASE32_INCORRECT_PADDING;
        }

        break;
      }

      buf[i] = base32_decode_char(c);
      if (buf[i] == 0xFF) {
        return BASE32_INCORRECT_SYMBOL;
      }

      i++;
    }

    // Handle incorrect values of dlen: 1, 3, 6

    switch (dlen) {
    case 8:
      dst[dsti + 4] = (buf[6] << 5) | buf[7];
      n++;
      // fallthrough

    case 7:
      dst[dsti + 3] = (buf[4] << 7) | (buf[5] << 2) | (buf[6] >> 3);
      n++;

    case 5:
      dst[dsti + 2] = (buf[3] << 4) | (buf[4] >> 1);
      n++;

    case 4:
      dst[dsti + 1] = (buf[1] << 6) | (buf[2] << 1) | (buf[3] >> 4);
      n++;

    case 2:
      dst[dsti + 0] = (buf[0] << 3) | (buf[1] >> 2);
      n++;
    }

    dsti += 5;
  }

  return n;
}
