#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static const char BASE32_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

static uint8_t decode_base32_char(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A';
  }

  if (c >= '2' && c <= '7') {
    return 26 + c - '2';
  }

  return 0xFF;
}

int base32_decode(const char *src, uint8_t *dst) {
  bool end = false;
  int dsti = 0;
  int n = 0;

  while (*src != 0 && !end) {
    uint8_t dbuf[8];
    int dlen = 8;

    for (int j = 0; j < 8;) {
      if (*src == 0) {
        dlen = j;
        end = true;
        break;
      }

      char c = *src;
      src++;

      if (isspace(c)) {
        continue;
      }

      int len = strlen(src);
      if (c == '=' && j >= 2 && len < 8) {
        // We've reached the end of the string and there is padding
        if (len + j < 8 - 1) {
          // corrupt input, not enough padding
          return -1;
        }

        for (int k = 0; k < 8 - 1 - j; k++) {
          if (len > k && src[k] != '=') {
            // incorrect padding
            return -2;
          }
        }

        dlen = j;
        end = true;

        if (dlen == 1 || dlen == 3 || dlen == 6) {
          // incorrect length
          return -3;
        }
        break;
      }

      dbuf[j] = decode_base32_char(c);
      if (dbuf[j] == 0xFF) {
        // invalid character
        return -4;
      }
      j++;
    }

    switch (dlen) {
    case 8:
      dst[dsti + 4] = dbuf[6] << 5 | dbuf[7];
      n++;
      // fallthrough

    case 7:
      dst[dsti + 3] = dbuf[4] << 7 | dbuf[5] << 2 | dbuf[6] >> 3;
      n++;

    case 5:
      dst[dsti + 2] = dbuf[3] << 4 | dbuf[4] >> 1;
      n++;

    case 4:
      dst[dsti + 1] = dbuf[1] << 6 | dbuf[2] << 1 | dbuf[3] >> 4;
      n++;

    case 2:
      dst[dsti] = dbuf[0] << 3 | dbuf[1] >> 2;
      n++;
    }
    dsti += 5;
  }

  return n;
}

void base32_encode(const uint8_t *src, char *dst, size_t len) {
  int si, di;
  si = di = 0;

  // Only encode full groups of 5 bytes
  int n = (len / 5) * 5;

  while (si < n) {
    // combine the binary into two <uint32_t>s so we can operate on contiguous
    // bytes with a single operation
    // using 32-bit words so that it can fit in a register on 32-bit platforms
    uint32_t hi = (src[si + 0] << 24) | (src[si + 1] << 16) |
                  (src[si + 2] << 8) | (src[si + 3]);
    uint32_t lo = (hi << 8) | (src[si + 4]);

    dst[di + 0] = BASE32_ALPHABET[hi >> 27 & 0x1F];
    dst[di + 1] = BASE32_ALPHABET[hi >> 22 & 0x1F];
    dst[di + 2] = BASE32_ALPHABET[hi >> 17 & 0x1F];
    dst[di + 3] = BASE32_ALPHABET[hi >> 12 & 0x1F];
    dst[di + 4] = BASE32_ALPHABET[hi >> 7 & 0x1F];
    dst[di + 5] = BASE32_ALPHABET[hi >> 2 & 0x1F];
    dst[di + 6] = BASE32_ALPHABET[lo >> 5 & 0x1F];
    dst[di + 7] = BASE32_ALPHABET[lo & 0x1F];

    si += 5;
    di += 8;
  }

  int remain = len - si;
  if (remain == 0)
    return;

  uint32_t val = 0;
  switch (remain) {
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
    val |= src[si] << 24;
    dst[di + 1] = BASE32_ALPHABET[val >> 22 & 0x1F];
    dst[di + 0] = BASE32_ALPHABET[val >> 27 & 0x1F];
  }

  int npad = (remain * 8 / 5) + 1;
  for (int i = npad; i < 8; i++) {
    dst[di + i] = '=';
  }
}
