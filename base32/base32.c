#include "base32.h"
#include <stdint.h>

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
